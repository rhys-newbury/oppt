#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <memory>

#include "oppt/problemEnvironment/ProblemEnvironmentOptions.hpp"
#include "oppt/problemEnvironment/ProblemEnvironment.hpp"
#include "solvers/ABT/solverABT.hpp"
#include "solvers/ABT/ABTOptions.hpp"

#include <gazebo/gazebo.hh>
#include <gazebo/common/Events.hh>
#include <gazebo/common/UpdateInfo.hh>
#include <typeinfo>


namespace {
    struct DummyGazeboEvent : public gazebo::event::Event {
        void Disconnect(int) override {}
    };

    // This ensures RTTI info is generated and kept in dynamic symbol table
    __attribute__((used))
    const std::type_info* force_gazebo_event_rtti_export = &typeid(DummyGazeboEvent);
}


// namespace {
//     struct DummyGazeboEvent : public gazebo::event::Event {
//         void Disconnect(int) override {}  // required to make it concrete
//     };

//     struct ForceGazeboRTTI {
//         ForceGazeboRTTI() {
//             DummyGazeboEvent dummy;
//             const gazebo::event::Event& ref = dummy;
//             (void)typeid(ref);  // Forces RTTI symbol generation
//         }
//     };
//     static const std::type_info& dummy_rtti = typeid(DummyGazeboEvent);

//     static ForceGazeboRTTI _force_gazebo_rtti;
// }
// namespace {
//     // struct DummyGazeboEvent : public gazebo::event::Event {
//     //     void Disconnect(int) override {}  // Make concrete
//     // };

// }


namespace py = pybind11;
using namespace oppt;

std::shared_ptr<ABTExtendedOptions> parse_abt_options_from_file(const std::string& configPath) {
    ProblemEnvironmentOptionsParser parser;
    std::cout << "configPath: " << configPath << std::endl;
    auto basePtr = parser.parseOptions<ABTExtendedOptions>(configPath);
    return std::dynamic_pointer_cast<ABTExtendedOptions>(basePtr);
}


PYBIND11_MODULE(oppt_py, m) {

    py::class_<ProblemEnvironment, std::shared_ptr<ProblemEnvironment>>(m, "ProblemEnvironment")
        .def(py::init<>())
        .def("initialize_with_options", &ProblemEnvironment::initializeWithOptions)
        .def("run_environment", &ProblemEnvironment::runEnvironment);

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
