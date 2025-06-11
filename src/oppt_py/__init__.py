import os
from pathlib import Path

if "OPPT_RESOURCE_PATH" not in os.environ:
    base = Path(__file__).resolve().parent.parent  # site-packages
    share = base / "share" / "oppt"
    plugins = share / "plugins"
    models = share / "models"
    os.environ["OPPT_RESOURCE_PATH"] = f"{plugins}:{models}"
    os.environ["GAZEBO_MODEL_PATH"] = f"{models}:"

from ._oppt_py import *  # exposes all C++ bindings
