from oppt_py import parse_abt_options_from_file, ProblemEnvironment

options = parse_abt_options_from_file("cfg/Rocksample.cfg")
env = ProblemEnvironment()
env.initialize_with_options(options)

env.run_environment()
