import os
from conan import ConanFile
from conan.tools.build import can_run


class ttysharkTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires("libmodbus/3.1.12")
        self.requires(self.tested_reference_str)

    def test(self):
        if can_run(self):
            self.run("ttyshark", env="conanrun")
