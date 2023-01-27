#!/usr/bin/env python3

import argparse
import os
import re

typeReplacements = [
    ('hmm_', 'HMM_'),

    ('vec', 'Vec'),
    ('mat', 'Mat'),
    ('quaternion', 'Quaternion'),
    ('bool', 'Bool'),
    ('.InternalElementsSSE', '.SSE'),
]

funcReplacements = [
    ('HMM_', 'HMM_'),
    
    ('Vec', 'V'),
    ('Mat', 'M'),
    ('Quaternion', 'Q'),
    ('Equals', 'Eq'),
    ('Subtract', 'Sub'),
    ('Multiply', 'Mul'),
    ('Divide', 'Div'),
    ('Inverse', 'Inv'),
    ('RSquareRoot', 'InvSqrt'),
    ('SquareRoot', 'Sqrt'),
    ('Squared', 'Sqr'),
    ('Length', 'Len'),

    ('Slerp', 'SLerp'),
    ('By', ''),
    ('LinearCombineSSE', 'LinearCombineV4M4'),
    ('Transpose', 'TransposeM4'),
    ('Fast', ''), # TODO(port): emit warning, lower precision
    ('Normalize', 'Norm'),
    ('ToRadians', 'ToRad')
]

handedFuncs = [
    'Perspective',
    'Rotate',
    'Orthographic',
    'LookAt',
    'FromAxisAngle',
    'ToQuaternion',
]

projectionFuncs = [
    'Perspective',
    'Orthographic',
]

numFiles = 0
numWarnings = 0

def printWarning(msg):
    global numWarnings
    numWarnings += 1
    print('WARNING: {}'.format(msg))

def updateFile(filename):
    global numFiles
    print('Updating: {}'.format(filename))
    numFiles += 1
    result = ''
    with open(filename, 'r', newline='') as f:
        for lineNo, line in enumerate(f):
            updatedLine = line

            def printLineWarning(msg):
                printWarning('  Line {}: {}'.format(lineNo + 1, msg))

            def replaceName(m):
                name = m.group()
                if name.startswith('hmm_'):
                    # do type replacements
                    for before, after in typeReplacements:
                        if before not in name:
                            continue
                        name = name.replace(before, after)
                else:
                    # do func replacements
                    for before, after in funcReplacements:
                        if before not in name:
                            continue
                        name = name.replace(before, after)

                        if after == 'LinearCombineV4M4':
                            printLineWarning('HMM_LinearCombineSSE is now HMM_LinearCombineV4M4, and will now use a fallback method when SSE is not available. You no longer need to check for the availability of SSE.')
                        if after == 'V' or after == 'M':
                            # uppercase the modifier, if any
                            name = re.sub(
                                r'[VM]\d[ivfd]?',
                                lambda m: m.group().upper(),
                                name
                            )
                            # and also nuke the integer constructors
                            vecIntMatch = re.search(r'(V\d)I', name)
                            if vecIntMatch:
                                name = name.replace(vecIntMatch.group(), vecIntMatch.group(1))

                    # add handedness / NDC modifiers
                    if not any(x in name for x in ['RH', 'LH', 'NO', 'ZO']):
                        for handedFunc in handedFuncs:
                            suffixed = handedFunc + '_RH'
                            if handedFunc in projectionFuncs:
                                suffixed += '_NO'
                            name = name.replace(handedFunc, suffixed)
                return name

            def wrapDegrees(m):
                name = m.group('name')
                arg = m.group('arg')
                if '(' in arg:
                    # all bets are off, don't wrap the argument
                    printLineWarning('{} now takes radians, but we were unable to automatically wrap the first argument with HMM_AngleDeg().'.format(name))
                    return m.group()
                return '{}(HMM_AngleDeg({}),'.format(name, arg)
                
            updatedLine = re.sub(r'(hmm_|HMM_)\w+', replaceName, updatedLine)
            updatedLine = re.sub(r'(?P<name>HMM_Perspective_RH_NO|HMM_Rotate_RH)\((?P<arg>.*?),', wrapDegrees, updatedLine)

            result += updatedLine

    with open(filename, 'w', newline='') as f:
        f.write(result)


parser = argparse.ArgumentParser(
    prog = 'update_hmm',
    description = 'Updates C and C++ source code to use Handmade Math 2.0.',
)
parser.add_argument(
    'filename', nargs='+',
    help='A file or directory to update to HMM 2.0. If a directory, all files with extensions from --exts will be processed.',
)
parser.add_argument(
    '--exts', nargs='+', default=['.c', '.cpp', '.h', '.hpp'],
    help='File extensions to run the script on, when targeting a directory. Default: .c, .cpp, .h, .hpp.',
    metavar='.foo',
)

args = parser.parse_args()

for path in args.filename:
    filenames = []
    if os.path.isfile(path):
        filenames = [path]
    else:
        for root, dirs, files in os.walk(path):
            for file in files:
                if file == 'HandmadeMath.h':
                    printWarning('HandmadeMath.h will not be replaced by this script.')
                elif file.endswith(tuple(args.exts)):
                    filenames.append(os.path.join(root, file))
    
    for filename in filenames:
        try:
            updateFile(filename)
        except UnicodeDecodeError:
            pass

    print('Updated {} files with {} warnings.'.format(numFiles, numWarnings))
