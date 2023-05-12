/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** CommandRunner
*/

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>

#ifndef COMMANDRUNNER_HPP_
    #define COMMANDRUNNER_HPP_

    class CommandRunner {
        public:
            class RunError {
                public:
                    class CommandNotFound : public std::exception {
                        public:
                            CommandNotFound(const std::string &cmd) : _message("Cannot find command " + cmd) {}
                            const char *what() const noexcept override {return _message.c_str(); }
                        private:
                            std::string _message;
                    };

                    class CommandFailed : public std::exception {
                        public:
                            CommandFailed(const std::string &cmd) : _message("Command " + cmd + " failed.") {}
                            const char *what() const noexcept override {return _message.c_str(); }
                        private:
                            std::string _message;
                    };
            };

            static std::string run(std::string cmd) {
                std::string result;
                char buffer[128];

                std::string command = getCommand(cmd);

                if (!isCommandExist(command))
                    throw CommandRunner::RunError::CommandNotFound(command);


                std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
                if (!pipe)
                    throw CommandRunner::RunError::CommandFailed(command);

                while (true) {
                    size_t n = std::fread(buffer, sizeof(char), sizeof(buffer), pipe.get());
                    if (n > 0) {
                        result.append(buffer, n);
                    } else if (std::feof(pipe.get())) {
                        break;
                    } else if (std::ferror(pipe.get())) {
                        throw CommandRunner::RunError::CommandFailed(command);
                    }
                }

                return result;
            }

            static bool isCommandExist(const std::string &cmd) {
                std::string command = "command -v " + cmd + " >/dev/null 2>&1";
                return std::system(command.c_str()) == 0;
            }
        private:
            static std::string getCommand(const std::string &cmd) {
                std::istringstream stream(cmd);
                std::string result;
                stream >> std::ws >> result;
                return result;
            }

    };

#endif /* !COMMANDRUNNER_HPP_ */
