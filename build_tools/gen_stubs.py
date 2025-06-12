#!/usr/bin/env python3
from pathlib import Path
import subprocess
import os
import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: gen_stubs.py <build_dir>")
        sys.exit(1)

    build_dir = Path(sys.argv[1]).resolve()
    module_name = "_oppt_py"
    output_dir = build_dir  # just drop it here

    env = os.environ.copy()
    env["PYTHONPATH"] = str(build_dir)

    subprocess.run([sys.executable, "-c", f"import {module_name}"], check=True, env=env)

    subprocess.run(
        ["pybind11-stubgen", module_name, "-o", str(output_dir)],
        check=True,
        cwd=build_dir,
        env=env
    )

    stub_file = output_dir / f"{module_name}.pyi"
    subprocess.run(["black", str(stub_file)], check=True)

if __name__ == "__main__":
    main()