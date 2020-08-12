##
## EPITECH PROJECT, 2019
## Visual Studio Live Share (Workspace)
## File description:
## player.py
##
from mysocket import MySocket
from random import randint
from enum import Enum
import time
import random

all_stones = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]

visions = [0, 3, 8, 15, 24, 35, 48, 63, 80]

dir_tab = [[""],["Forward"], ["Left", "Forward"], ["Left", "Forward"], ["Left", "Forward"], ["Left", "Left"], ["Right", "Forward"], ["Right", "Forward"], ["Right", "Forward"]]

debug = False
#requirements for each level
need_stones = [{},
    {
        "player": 1,
        "linemate": 1,
        "deraumere": 0,
        "sibur": 0,
        "mendiane": 0,
        "phiras": 0,
        "thystame": 0
    },
    {
        "player": 2,
        "linemate": 1,
        "deraumere": 1,
        "sibur": 1,
        "mendiane": 0,
        "phiras": 0,
        "thystame": 0
    },
    {
        "player": 2,
        "linemate": 2,
        "deraumere": 0,
        "sibur": 1,
        "mendiane": 0,
        "phiras": 2,
        "thystame": 0
    },
    {
        "player": 4,
        "linemate": 1,
        "deraumere": 1,
        "sibur": 2,
        "mendiane": 0,
        "phiras": 1,
        "thystame": 0
    },
    {
        "player": 4,
        "linemate": 1,
        "deraumere": 2,
        "sibur": 1,
        "mendiane": 3,
        "phiras": 0,
        "thystame": 0
    },
    {
        "player": 6,
        "linemate": 1,
        "deraumere": 2,
        "sibur": 3,
        "mendiane": 0,
        "phiras": 1,
        "thystame": 0
    },
    {
        "player": 6,
        "linemate": 2,
        "deraumere": 2,
        "sibur": 2,
        "mendiane": 2,
        "phiras": 2,
        "thystame": 1
    }
]

class Player:

    def __init__(self):
        self.socket = 0
        self.level = 1
        self.food = 1260
        self.stones = {
            "linemate" : 0,
            "deraumere" : 0,
            "sibur" : 0,
            "mendiane" : 0,
            "phiras" : 0,
            "thystame" : 0
        }
        self.team_name = ""
        self.dir = -1
        self.needed_list = []
        self.last_move = ""
        self.inventory = []
        self.following = 0
        self.next_dir = []

    def connect(self, infos):
        self.socket = MySocket(infos["machine"], int(infos["port"]))
        return (self.socket.connect())

    def init_player(self, infos):
        self.team_name = infos["name"]
        self.connect(infos)

    def preliminaries(self):
        self.parse_rcv_msg(None)
        self.socket.send_msg(self.team_name)
        if self.parse_rcv_msg(None) == "ko":
            exit (0)

    def Look(self):
        self.socket.send_msg("Look")
        map = self.parse_rcv_msg("Look")
        return (map)

    def check_needed_object(self):
        self.needed_list = []
        for stone in all_stones:
            if self.stones[stone] < need_stones[self.level][stone]:
                self.needed_list.append(stone)

    def make_move(self):
        directions = self.next_dir
        for direction in directions:
            self.socket.send_msg(direction)
            msg = self.parse_rcv_msg("Join Player")
            while msg != "ok":
                msg = self.parse_rcv_msg("Join Player")
        self.next_dir = []

    def handle_broadcast(self, tab_msg):
        for msg in tab_msg:
            if (("ready" in msg) and (self.dir != 0)):
                tab = msg.split(":");
                if (int(tab[1]) == self.level):
                    if (int(tab[2]) == self.following):
                        tmp = tab[0].split(" ")[1]
                        self.dir = int(tmp.split(",")[0])
                        self.next_dir = dir_tab[self.dir]
                        if debug:
                            print("JE SUIS LE JOUEUR AVEC L'ID", self.following, "Tab =", self.next_dir, "Dir =", self.dir)
                    elif (self.following == 0):
                        self.following = int(tab[2])
                        tmp = tab[0].split(" ")[1]
                        self.dir = int(tmp.split(",")[0])
                        self.next_dir = dir_tab[self.dir]
                        if debug:
                            print("JE COMMENCE A SUIVRE", tab[2], "Tab =", self.next_dir, "Dir =", self.dir)
            elif ("start" in msg):
                tab = msg.split(":")
                if (int(tab[1]) == self.level):
                    tmp = tab[0].split(" ")[1]
                    if (int(tab[2]) == self.following and self.dir != 0):
                        self.dir = -1
                        self.following = 0
                    elif (int(tab[2]) == self.following):
                        self.dir = int(tmp.split(",")[0])

    def parse_rcv_msg(self, command):
        msg = self.socket.rcv_msg()
        tab_msg = msg.split("\n")
        broadcast = []
        msg_final = ""
        for tab in tab_msg:
            if (len(tab) == 0):
                continue
            elif "message" in tab:
                broadcast.append(tab)
            elif "Current level" in tab:
                self.level = self.level + 1
                self.dir = -1
                msg_final = tab
            else:
                msg_final = tab
        self.handle_broadcast(broadcast)
        if (len(msg_final) == 0):
            msg_final = self.parse_rcv_msg(command)
        elif (command != None and (("Look" in command) or ("Inventory" in command)) and (msg_final[0] != "[")):
            msg_final = self.parse_rcv_msg(command)
        return msg_final

    def move(self, i):
        if debug:
            print("Je vais vers une pierre")
        average = 0
        j = 0
        moves = []
        for vision in visions:
            if (i > vision):
                j = j + 1
        if (((visions[j] + (visions[j - 1])) % 2) == 1):
            average = (visions[j] + (visions[j - 1] + 1)) / 2
        else:
            average = (visions[j] + (visions[j - 1])) / 2
        while j > 0:
            moves.append("Forward")
            j = j - 1
        if (i < average):
            moves.append("Left")
            while i < average:
                moves.append("Forward")
                i = i + 1
        elif (i > average):
            moves.append("Right")
            while i > average:
                moves.append("Forward")
                i = i - 1
        self.next_dir = moves

    def take_food(self, view):
        tabs = view.split(", ")
        nb_food = 0
        while tabs[0].find("food") != -1 and self.dir == -1:
            self.socket.send_msg("Take food")
            msg = self.parse_rcv_msg("Join Player")
            if msg == "ko" or nb_food > 10:
                break
            nb_food += 1

    def choose_action(self, view):
        tabs = view.split(", ")
        for need in self.needed_list:
            i = 0
            for tab in tabs:
                if (tab.find(need) != -1 and self.dir == -1):
                    if (i == 0):
                        self.socket.send_msg("Take " + need)
                        self.parse_rcv_msg("Take")
                        return
                    else:
                        self.move(i)
                        return
                i = i + 1
        self.move_random()

    def check_inventory(self):
        self.socket.send_msg("Inventory")
        self.inventory = self.parse_rcv_msg("Inventory")
        tab = self.inventory.split(", ")
        for stone in tab:
            stone_name = stone.split(" ")
            if ((stone_name[0] != "food") and (stone_name[0] != "[")):
                self.stones[stone_name[0]] = int(stone_name[1])

    def move_random(self):
        if debug:
            print("Move random")
        rnd = random.Random()
        if (self.last_move == "Left"):
            move = rnd.choice(["Forward", "Right"])
        elif (self.last_move == "Right"):
            move = rnd.choice(["Forward", "Left"])
        else:
            move = rnd.choice(["Forward", "Left", "Right"])
        self.last_move = move
        self.next_dir = [move]

    def drop_inventory(self):
        for stone in all_stones:
            needed = need_stones[self.level][stone]
            while needed > 0:
                self.socket.send_msg("Set " + stone)
                msg = self.parse_rcv_msg("Set")
                if msg == "ok":
                    needed = needed - 1
                else:
                    break;

    def take_other_stones(self):
        view = self.Look()
        tabs = view.split(", ")
        for stone in all_stones:
            while tabs[0].find(stone) != -1:
                self.socket.send_msg("Take " + stone)
                if self.parse_rcv_msg("Take") == "ko":
                    break

    def make_incantation(self):
        self.following = randint(1000, 10000)
        if (self.level >= 2):
            while (self.check_nb_player_tile() == 0):
                if debug:
                    print("self.level = ", self.level)
                    print("(need_stones[self.level][\"player\"] - 1) = ", (need_stones[self.level]["player"] - 1))
                self.socket.send_msg("Broadcast ready for incantation :" + str(self.level) + ":" + str(self.following))
                self.parse_rcv_msg("Broadcast")
        self.socket.send_msg("Broadcast start incantation :" + str(self.level) + ":" + str(self.following))
        self.parse_rcv_msg("Broadcast")
        self.take_other_stones()
        self.drop_inventory()
        self.eject_player()
        view = self.Look()
        if (self.check_nb_player_tile() == 1):
            self.socket.send_msg("Incantation")
            msg = self.parse_rcv_msg("Incantation")
            msg = self.parse_rcv_msg("Incantation")
        self.following = 0
        self.dir = -1

    def check_nb_player_tile(self):
        view = self.Look()
        player_tile = view.split(",")[0][1:]
        all_objects = player_tile.split(" ")
        need_player = need_stones[self.level]["player"]
        for obj in all_objects:
            if obj == "player":
                if (need_player > 0):
                    need_player -= 1;
        if (need_player == 0):
            return (1)
        elif (need_player > 0):
            return (0)

    def eject_player(self):
        view = self.Look()
        player_tile = view.split(",")[0][1:]
        all_objects = player_tile.split(" ")
        need_player = need_stones[self.level]["player"]
        for obj in all_objects:
            if obj == "player":
                if (need_player > 0):
                    need_player -= 1;
                else:
                    self.socket.send_msg("Eject")
                    msg = self.socket.rcv_msg()
                    self.socket.send_msg("Forward")
                    self.parse_rcv_msg("Forward")
                    return;

    def wait_incantation(self):
        msg = ""
        if self.dir == 0:
            lvl = self.level
            while ((self.level == lvl)):
                msg = self.parse_rcv_msg("wait incantation")
                if ("ko" in msg):
                    break
            self.dir = -1
            self.following = 0

    def play(self):
        self.preliminaries()
        while 1:
            if debug:
                print(">> play LEVEL =", self.level, "\n\n\n")
            self.wait_incantation()
            self.check_inventory()
            self.check_needed_object()
            if ((not self.needed_list) and self.following == 0):
                self.make_incantation()
            else:
                view = self.Look()
                self.take_food(view)
                if (self.dir == -1):
                    self.choose_action(view)
                if ((len(self.next_dir) != 0) and (len(self.next_dir[0]) != 0)):
                    print("Make move : ", self.next_dir)
                    self.make_move()