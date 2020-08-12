##
## EPITECH PROJECT, 2020
## main
## File description:
## zappy
##

import sys
from parser import Parser
from player import Player

parser = Parser()
player = Player()

def main():
    infos = parser.parse_arg(sys.argv)
    if infos == None:
        return (84)
    print("name : ", infos["name"])
    print("port : ", infos["port"])
    print("machine : ", infos["machine"])
    player.init_player(infos)
    player.play()

main()