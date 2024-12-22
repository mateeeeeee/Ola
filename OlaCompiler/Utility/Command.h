#pragma once


namespace ola
{
	Int ExecuteCommand(Char const* cmd);
	Int ExecuteCommand_NonBlocking(Char const* cmd, Float timeout);
}