#!/usr/bin/env python
from conans import ConanFile, CMake


class CatchConan(ConanFile):
    name = "Catch2"
    version = "2.11.1"
    description = "A modern, C++-native, header-only, framework for unit-tests, TDD and BDD"
    topics = ("conan", "catch2", "header-only", "unit-test", "tdd", "bdd")
    url = "https://github.com/catchorg/Catch2"
    homepage = url
    license = "BSL-1.0"
    exports = "LICENSE.txt"
    exports_sources = ("single_include/*", "CMakeLists.txt", "CMake/*", "contrib/*")
    no_copy_source = True
    generators = "cmake"

    def package(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_TESTING"] = False
        cmake.definitions["CATCH_BUILD_TESTING"] = False
        cmake.definitions["CATCH_BUILD_EXAMPLES"] = False
        cmake.definitions["CATCH_BUILD_EXTRA_TESTS"] = False
        cmake.definitions["CATCH_ENABLE_COVERAGE"] = False
        cmake.definitions["CATCH_ENABLE_WERROR"] = False
        cmake.definitions["CATCH_INSTALL_DOCS"] = False
        cmake.definitions["CATCH_INSTALL_HELPERS"] = True
        cmake.configure()
        cmake.install()

        self.copy(pattern="LICENSE.txt", dst="licenses")

    def package_id(self):
        self.info.header_only()
