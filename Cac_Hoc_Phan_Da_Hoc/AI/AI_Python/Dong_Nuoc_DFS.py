import os

action = ["First State", "Pour Water Full X", "Pour Water Full Y",
          "Pour Water Empty X", "Pour Water Empty Y",
          "Pour Water X to Y", "Pour Water Y to X"]
id = 0
tankcapacity_X = 9
tankcapacity_Y = 4
open = []
close = []
goal = 6


class State:
    def __init__(self, x, y, id, idcha, opt):
        self.x = x
        self.y = y
        self.id = id
        self.idcha = idcha
        self.opt = opt

    def printState(self):
        print(action[self.opt])
        print("X =", self.x, ", Y =", self.y)


def pourWaterFullX(cur, re):
    global tankcapacity_X
    global tankcapacity_Y
    if cur.x < tankcapacity_X:
        re.x = tankcapacity_X
        re.y = cur.y
        return 1
    return 0


def pourWaterFullY(cur,   re):
    global tankcapacity_X
    global tankcapacity_Y
    if (cur.y < tankcapacity_Y):
        re.y = tankcapacity_Y
        re.x = cur.x
        return 1
    return 0


def pourWaterEmptyX(cur,   re):
    global tankcapacity_X
    global tankcapacity_Y
    if (cur.x > 0):
        re.x = 0
        re.y = cur.y
        return 1
    return 0


def pourWaterEmptyY(cur,   re):
    global tankcapacity_X
    global tankcapacity_Y
    if (cur.y > 0):
        re.y = 0
        re.x = cur.x
        return 1
    return 0


def pourWaterXY(cur,   re):
    global tankcapacity_X
    global tankcapacity_Y
    if (cur.x > 0 and cur.y < tankcapacity_Y):
        re.x = cur.x - (tankcapacity_Y - cur.y)
        if (re.x < 0):
            re.x = 0
        re.y = (cur.y + cur.x)
        if (re.y > tankcapacity_Y):
            re.y = tankcapacity_Y
        return 1
    return 0


def pourWaterYX(cur,   re):
    global tankcapacity_X
    global tankcapacity_Y
    if (cur.x < tankcapacity_X and cur.y > 0):
        re.x = cur.x + cur.y
        if (re.x > tankcapacity_X):
            re.x = tankcapacity_X
        re.y = cur.y - (tankcapacity_X - cur.x)
        if (re.y < 0):
            re.y = 0
        return 1
    return 0


def call_operator(cur,  re, opt):
    if opt == 1:
        return pourWaterFullX(cur, re)
    if opt == 2:
        return pourWaterFullY(cur, re)
    if opt == 3:
        return pourWaterEmptyX(cur, re)
    if opt == 4:
        return pourWaterEmptyY(cur, re)
    if opt == 5:
        return pourWaterXY(cur, re)
    if opt == 6:
        return pourWaterYX(cur, re)


def goalCheck(node):
    global goal
    if node.x == goal or node.y == goal:
        return 1
    return 0


def findState(state, stack):
    for i in range(0, len(stack)):
        node = stack[i]
        if state.x == node.x and state.y == node.y:
            return 1
    return 0


def DFS_Algorithm(state):
    global id
    global open
    global close
    open.append(state)
    while len(open) != 0:
        node = open.pop()
        close.append(node)
        if goalCheck(node):
            return node

        for opt in range(1, 7):
            newNode = State(0, 0, id, node.id, opt)
            id += 1
            if call_operator(node, newNode, opt):
                if findState(newNode, open) or findState(newNode, close):
                    continue
                open.append(newNode)
    return None


list = []


def printGoal(state):
    global list
    global close
    list.append(state)
    idcha = state.idcha
    while idcha != 0:
        for i in range(0, len(close)):
            node = close[i]
            if idcha == node.id:
                list.append(node)
                idcha = node.idcha
    count = 1
    print("CAC BUOC:")
    while len(list) != 0:
        print("Buoc ", count)
        count += 1
        node = list.pop()
        node.printState()
        print("------------------------")


def main():
    global id
    state = State(0, 0, 0, 0, 0)
    id += 1
    node = DFS_Algorithm(state)
    if node == None:
        print("None")
    else:
        printGoal(node)
    quit()


if __name__ == "__main__":
    os.system("cls")
    main()
