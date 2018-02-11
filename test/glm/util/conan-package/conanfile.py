import os
from conans import ConanFile

class GlmConan(ConanFile):
    name = "glm"
    version = "master"
    generators = "txt"
    url="https://github.com/g-truc/glm"
    description="OpenGL Mathematics (GLM)"
    license = "https://github.com/g-truc/glm/blob/manual/copying.txt"
    exports_sources = ["FindGLM.cmake", os.sep.join(["..", "..", "glm*"])]
    exports = "lib_licenses/*"

    def build(self):
        self.output.info("No compilation necessary for GLM")

    def package(self):
        self.copy("FindGLM.cmake", ".", ".")
        self.copy("*", src="glm", dst=os.sep.join([".", "include", "glm"]))
        self.copy("lib_licenses/license*", dst="licenses",  ignore_case=True, keep_path=False)
