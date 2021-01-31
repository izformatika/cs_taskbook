def graph0():
    print("                               ")
    print("                               ")
    print("     _______                   ")
    print("    |\      |                  ")
    print("    | \     |                  ")
    print("    |  |    |                  ")
    print("    |  |    |                  ")
    print("    |  |    |                  ")
    print("    |  |    |                  ")
    print("    | o|    |                  ")
    print("    |  |    |                  ")
    print("    |  |    |                  ")
    print("___ |  |____|__________________")
    print("     \ |              _ID      ")
    print("      \|               _ID     ")
    print("                               ")

def graph1():
    print("                               ")
    print("                               ")
    print("     _______                   ")
    print("    |\      |                  ")
    print("    | \     |                  ")
    print("    |  |    |                  ")
    print("    |  |    |                  ")
    print("    |  |    |                  ")
    print("    |  |    |                  ")
    print("    | o|    |                  ")
    print("    |  |    |                  ")
    print("    |  |    |                  ")
    print("___ |  |____|_______U__U_______")
    print("     \ |   '  '  ` .VD VD '    ")
    print("      \|       '  ` ' . `. `   ")
    print("                               ")

def graph2():
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("      T----~~~~~~~--T          ")
    print("______|\     ~~~~~~  \_________")
    print("     \  T-------------T        ")
    print("      \ |             |        ")
    print("       \,,,,,,,,,,,,,,,,       ")

def graph3():
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("                               ")
    print("       _____ooo___U_           ")
    print("      T\  w \_/     \          ")
    print("      | \_|__________\         ")
    print("______|_T____________ T________")
    print("        |             |        ")
    print("        |             |        ")
    print("                               ")
def graph4():
    print("          ╔╗ ╔╗                ")
    print("          ║║ ║║                ")
    print("╔╗╔╗╔╗╔══╗║║ ║║                ")
    print("║╚╝╚╝║║╔╗║║║ ║║                ")
    print("╚╗╔╗╔╝║║═╣║╚╗║╚╗               ")
    print(" ╚╝╚╝ ╚══╝╚═╝╚═╝               ")
    print("                               ")
    print("  ╔╗                           ")
    print("  ║║                           ")
    print("╔═╝║╔══╗╔═╗ ╔══╗               ")
    print("║╔╗║║╔╗║║╔╗╗║╔╗║               ")
    print("║╚╝║║╚╝║║║║║║║═╣               ")
    print("╚══╝╚══╝╚╝╚╝╚══╝               ")
    print("                               ")
    print("                               ")
    print("                               ")
def graph5():
    pass
    '''
    print("                               ")
    print("                               ")
    print("╔╗ ╔╗╔══╗╔╗╔╗                  ")
    print("║║ ║║║╔╗║║║║║                  ")
    print("║╚═╝║║╚╝║║╚╝║                  ")
    print("╚═╗╔╝╚══╝╚══╝                  ")
    print("╔═╝║                           ")
    print("╚══╝                           ")
    print("  ╔╗        ╔╗                 ")
    print("  ║║        ║║                 ")
    print("╔═╝║╔╗╔══╗╔═╝║                 ")
    print("║╔╗║╠╣║╔╗║║╔╗║                 ")
    print("║╚╝║║║║║═╣║╚╝║                 ")
    print("╚══╝╚╝╚══╝╚══╝                 ")
    print("                               ")
    '''
game = {
    0: ["you are in your flat's lobby", 
            [
                ["take off your shoes", 1, 1],
                ["go to bedroom", 2, 0],
                ["go to kitchen", 3, 0]
            ],
        graph0
        ],
    1: ["you are in your flat's lobby", 
            [
                ["go to bedroom", 2, 0],
                ["go to kitchen", 3, 0]
            ],
        graph1
        ],
    2: ["you can't go to sleep while starving", 
            [
                ["go to kitchen", 3, 0],
                ["go to lobby", 1, 0]
            ],
        graph2
        ],
    3: ["you are in the kitchen", 
            [
                ["drink water", 3, 1],
                ["eat PELMESHKI", 4, 1]
            ],
        graph3
        ],
    4: ["you are full", 
            [
                ["go to bedroom", 6, 0],
                ["go to lobby", 5, 0],
                ["eat more PELMESHKI", 8, 0]
            ],
        graph3
        ],
    5: ["you are in your flat's lobby", 
            [
                ["go to bedroom", 6, 0],
                ["go to kitchen", 4, 0]
            ],
        graph1
        ],
    6: ["you are in your bedroom", 
            [
                ["go to lobby", 5, 0],
                ["go to kitchen", 4, 0],
                ["sleep", 7, 1]
            ],
        graph2
        ],
    7: ["you are asleep",
            [],
        graph4
        ],
    8: ["you ate too much, you feel sick",
            [],
        graph5
        ]
    }
start_state = 0
win_states = [7]
lose_states = [8]
welcome_text = "YOU WANT TO SLEEP SO HARD"
#===================================================
cur_state = start_state
points = 0
while True:
    print(welcome_text)
    print("Points: " + str(points))
    print(game[cur_state][0])
    game[cur_state][2]()
    if cur_state in win_states:
        print("You win!")
        break
    elif cur_state in lose_states:
        print("You lose!")
        break
    if len(game[cur_state][1]) > 0:
        for move in range(len(game[cur_state][1])):
            print(str(move + 1) + ". " + game[cur_state][1][move][0])
        try:
            choice = int(input("Введите номер действия: ")) - 1
        except:
            choice = -1
        if 0 <= choice < len(game[cur_state][1]):
            points += game[cur_state][1][choice][2]
            cur_state = game[cur_state][1][choice][1]

        print()
