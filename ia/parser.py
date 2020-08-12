##
## EPITECH PROJECT, 2019
## Visual Studio Live Share (Workspace)
## File description:
## parser.py
##

class Parser:

    def zappy_help(self, bin):
        print("USAGE: ", bin, "-p port -n name -h machine")
        print("\tport\tis the port number")
        print("\tname\tis the name of the team")
        print("\tmachine\tis the name of the machine; localhost by default")

    def help_flag(self, argv):
        for flag in argv:
            if flag == "-help":
                self.zappy_help(argv[0])
                return (True)
        return (False)

    def name_flag(self, argv, infos):
        i = 0
        for flag in argv:
            if (flag == "-n") & (len(argv) > (i + 1)):
                infos["name"] = argv[i + 1]
                return (True)
            i = i + 1
        return (False)

    def machine_flag(self, argv, infos):
        i = 0
        for flag in argv:
            if flag == "-h":
                infos["machine"] = argv[i + 1]
                return (True)
            i = i + 1
        return (False)

    def port_flag(self, argv, infos):
        i = 0
        for flag in argv:
            if flag == "-p":
                infos["port"] = argv[i + 1]
                return (True)
            i = i + 1
        return (False)

    def parse_arg(self, argv):
        infos = {
            "name": "",
            "port": 0,
            "machine": "localhost"
        }
        if (len(argv) == 1):
            return (None)
        if (self.help_flag(argv) == True):
            exit(0);
        else:
            self.machine_flag(argv, infos)
            if self.name_flag(argv, infos) == False:
                return (None)
            if self.port_flag(argv, infos) == False:
                return (None)
            return (infos)
