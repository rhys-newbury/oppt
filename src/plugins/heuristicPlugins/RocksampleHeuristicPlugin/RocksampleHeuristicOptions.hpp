#pragma once
#include "oppt/plugin/PluginOptions.hpp"

namespace oppt
{
class RocksampleHeuristicOptions: public PluginOptions {
public:
	using PluginOptions::PluginOptions;

	FloatType exitReward = 0.0;

	FloatType goodRockSamplingReward = 0.0;

	static std::unique_ptr<options::OptionParser> makeParser() {
		std::unique_ptr<options::OptionParser> parser =
		    PluginOptions::makeParser();
		addRocksampleRewardOptions(parser.get());
		return std::move(parser);
	}

	static void addRocksampleRewardOptions(options::OptionParser* parser) {
		parser->addOption<FloatType>("rewardPluginOptions", "exitReward", &RocksampleHeuristicOptions::exitReward);
		parser->addOption<FloatType>("rewardPluginOptions", "goodRockSamplingReward", &RocksampleHeuristicOptions::goodRockSamplingReward);
	}

};
}
