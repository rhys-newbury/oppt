from oppt_py import (
    parse_abt_options_from_file,
    ProblemEnvironment,
    create_abt_environment,
)
from pathlib import Path

for p in Path("/app/cfg").glob("*.cfg"):
    options = parse_abt_options_from_file(str(p))
    env = create_abt_environment()
    env.initialize_with_options(options)
    result = env.run_environment()
