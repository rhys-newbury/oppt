from oppt_py import (
    parse_abt_options_from_file,
    ProblemEnvironment,
    create_abt_environment,
)

options = parse_abt_options_from_file("cfg/Rocksample.cfg")

env = create_abt_environment()

print(options)
# env.setup()
env.initialize_with_options(options)
print("starting to run..")
result = env.run_environment()
print(result.average_total_discounted_reward)
