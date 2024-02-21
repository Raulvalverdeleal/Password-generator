#include <iostream>
#include <sstream>
#include <stdio.h>
#include "clipboard.hpp"

std::string Clipboard::exec(const char *cmd)
{
	FILE *pipe = popen(cmd, "r");
	if (!pipe) return "ERROR";
	char buffer[128];
	std::string result = "";
	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe) != NULL) result += buffer;
	}
	pclose(pipe);
	return result;
}

std::string Clipboard::paste()
{
	return this->exec("pbpaste");
}

std::string Clipboard::copy(const char *new_clipboard)
{
	std::stringstream cmd;
	cmd << "echo \"" << new_clipboard << "\" | pbcopy";
	return this->exec(cmd.str().c_str());
}

Clipboard clipboard;
