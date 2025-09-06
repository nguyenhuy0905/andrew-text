from conan import ConanFile
from conan.tools.cmake import cmake_layout

class Recipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        # our text gui
        self.requires("raylib/5.5")

    def build_requirements(self):
        self.test_requires("gtest/[>=1.14.0]")
