#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <memory>

#include "oppt/problemEnvironment/ProblemEnvironmentOptions.hpp"
#include "oppt/problemEnvironment/ProblemEnvironment.hpp"
#include "solvers/ABT/solverABT.hpp"
#include "solvers/ABT/ABTOptions.hpp"
#include "solvers/ABT/robotModel/solver/Solver.hpp"


#ifdef _WIN32
#include <windows.h>
#endif

void set_env(const std::string& name, const std::string& value) {
#ifdef _WIN32
    _putenv_s(name.c_str(), value.c_str());
#else
    setenv(name.c_str(), value.c_str(), 1); // overwrite = 1
#endif
}

namespace py = pybind11;
using namespace oppt;

std::shared_ptr<ABTExtendedOptions> parse_abt_options_from_file(const std::string& configPath) {
    ProblemEnvironmentOptionsParser parser;
    std::cout << "configPath: " << configPath << std::endl;
    auto basePtr = parser.parseOptions<ABTExtendedOptions>(configPath);
    return std::dynamic_pointer_cast<ABTExtendedOptions>(basePtr);
}

std::shared_ptr<ProblemEnvironment> create_abt_env() {
    auto env = std::make_shared<ProblemEnvironment>();
    env->create<solvers::ABT>();
    return env;
}


PYBIND11_MODULE(_oppt_py, m) {

    try {
        py::object pathlib = py::module_::import("pathlib");

        // This gets the path to _oppt_py.so inside oppt_py/
        py::object oppt_module = py::module_::import("oppt_py");
        py::object oppt_file = oppt_module.attr("__file__");  // e.g. /usr/.../oppt_py/_oppt_py.so
        py::object oppt_path = pathlib.attr("Path")(oppt_file);

        // Go up two levels (from oppt_py/_oppt_py.so → site-packages → root)
        py::object site_packages = oppt_path.attr("parent").attr("parent");

        // Append share/oppt/plugins
        py::object plugins_path = site_packages
            .attr("__truediv__")("share")
            .attr("__truediv__")("oppt")
            .attr("__truediv__")("plugins");

        py::object models_path = site_packages
            .attr("__truediv__")("share")
            .attr("__truediv__")("oppt")
            .attr("__truediv__")("models");

        std::string plugin_str = py::str(plugins_path);
        std::string model_str = py::str(models_path);       
        std::string full_path = plugin_str + ":" + model_str;
 
        set_env("OPPT_RESOURCE_PATH", full_path);

    } catch (const std::exception& e) {
        // Fallback: don’t crash if something went wrong
        py::print("Warning: could not set OPPT_RESOURCE_PATH:", e.what());
    }

    py::class_<RunSummary>(m, "RunSummary")
    .def_readonly("mean_num_steps", &RunSummary::meanNumSteps)
    .def_readonly("mean_planning_time_per_step", &RunSummary::meanPlanningTimePerStep)
    .def_readonly("num_successful_runs", &RunSummary::numSuccessfulRuns)
    .def_readonly("percentage_successful_runs", &RunSummary::percentageSuccRuns)
    .def_readonly("average_total_discounted_reward", &RunSummary::averageTotalDiscountedReward);



    py::class_<ProblemEnvironment, std::shared_ptr<ProblemEnvironment>>(m, "ProblemEnvironment")
        .def(py::init<>())
        .def("initialize_with_options", &ProblemEnvironment::initializeWithOptions)
        .def("run_environment", &ProblemEnvironment::runEnvironment);

    m.def("create_abt_environment", &create_abt_env, "Create ABT solver environment");


    py::class_<ProblemEnvironmentOptions, std::shared_ptr<ProblemEnvironmentOptions>>(m, "ProblemEnvironmentOptions")
        .def(py::init<>())
        .def_readwrite("robotName", &ProblemEnvironmentOptions::robotName)
        .def_readwrite("planningEnvironmentPath", &ProblemEnvironmentOptions::planningEnvironmentPath)
        .def_readwrite("executionEnvironmentPath", &ProblemEnvironmentOptions::executionEnvironmentPath)
        .def_readwrite("discountFactor", &ProblemEnvironmentOptions::discountFactor)
        .def_readwrite("stepTimeout", &ProblemEnvironmentOptions::stepTimeout)
        .def_readwrite("nRuns", &ProblemEnvironmentOptions::nRuns)
        .def_readwrite("nSimulationSteps", &ProblemEnvironmentOptions::nSimulationSteps)
        .def_readwrite("planningRewardPlugin", &ProblemEnvironmentOptions::planningRewardPlugin)
        .def_readwrite("executionRewardPlugin", &ProblemEnvironmentOptions::executionRewardPlugin)
        .def_readwrite("planningTerminalPlugin", &ProblemEnvironmentOptions::planningTerminalPlugin)
        .def_readwrite("executionTerminalPlugin", &ProblemEnvironmentOptions::executionTerminalPlugin)
        .def_readwrite("planningTransitionPlugin", &ProblemEnvironmentOptions::planningTransitionPlugin)
        .def_readwrite("executionTransitionPlugin", &ProblemEnvironmentOptions::executionTransitionPlugin)
        .def_readwrite("planningObservationPlugin", &ProblemEnvironmentOptions::planningObservationPlugin)
        .def_readwrite("executionObservationPlugin", &ProblemEnvironmentOptions::executionObservationPlugin)
        .def_readwrite("initialBeliefPluginPlanning", &ProblemEnvironmentOptions::initialBeliefPluginPlanning)
        .def_readwrite("initialBeliefPluginExecution", &ProblemEnvironmentOptions::initialBeliefPluginExecution)
        .def_readwrite("heuristicPlugin", &ProblemEnvironmentOptions::heuristicPlugin)
        .def_readwrite("saveParticles", &ProblemEnvironmentOptions::saveParticles)
        .def_readwrite("overwriteExistingLogFiles", &ProblemEnvironmentOptions::overwriteExistingLogFiles)
        .def_readwrite("logPath", &ProblemEnvironmentOptions::logPath);

    py::class_<ABTExtendedOptions, ProblemEnvironmentOptions, std::shared_ptr<ABTExtendedOptions>>(m, "ABTExtendedOptions")
        .def(py::init<>())
        .def_readwrite("configPath", &ABTExtendedOptions::configPath)
        .def_readwrite("logPath", &ABTExtendedOptions::logPath)
        .def_readwrite("seed", &ABTExtendedOptions::seed)
        .def_readwrite("heuristicPlugin", &ABTExtendedOptions::heuristicPlugin)
        .def_readwrite("enableGazeboStateLogging", &ABTExtendedOptions::enableGazeboStateLogging)
        .def_readwrite("hasVerboseOutput", &ABTExtendedOptions::hasVerboseOutput);


    m.def("parse_abt_options_from_file", &parse_abt_options_from_file,
        py::arg("configPath"),
        "Parse ABTExtendedOptions from a config file.");


}
