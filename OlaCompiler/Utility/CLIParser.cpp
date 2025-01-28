#include "CLIParser.h"

namespace ola
{
	CLIParseResult::CLIParseResult(std::vector<CLIArg> const& args, std::unordered_map<std::string, Uint32> const& prefix_index_map)
	{
		for (auto const& [prefix, index] : prefix_index_map)
		{
			cli_arg_map[prefix] = args[index];
		}
	}

	CLIParseResult CLIParser::Parse(Int argc, Char** argv)
	{
		std::unordered_map<std::string, CLIArg> cli_arg_map;
		for (Int i = 0; i < argc; ++i)
		{
			std::string arg = argv[i];
			if (prefix_arg_index_map.find(arg) != prefix_arg_index_map.end())
			{
				Uint32 arg_index = prefix_arg_index_map[arg];
				CLIArg& cli_arg = args[arg_index];
				cli_arg.SetIsPresent();
				if (cli_arg.has_value)
				{
					while (i + 1 < argc && !prefix_arg_index_map.contains(argv[i + 1]))
					{
						cli_arg.AddValue(argv[++i]);
					}
					if (cli_arg.values.empty())
					{
						OLA_ASSERT_MSG(false, "Missing value for cmdline argument");
					}
				}
			}
		}

		for (CLIArg const& arg : args)
		{
			for (std::string const& prefix : arg.prefixes)
			{
				cli_arg_map[prefix] = arg;
			}
		}

		return CLIParseResult(args, prefix_arg_index_map);
	}

}
