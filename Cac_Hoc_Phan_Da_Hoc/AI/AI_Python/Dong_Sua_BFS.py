import os
os.system("cls")

tank_X = 10
tank_Y = 5
tank_Z = 6
goal = 8
empty = 0
open = []
close = []
id = 0


action = ["First Action", "X-->Y", "X-->Z", "Y-->X", "Y-->Z", "Z-->X", "Z-->Y"]


class State:
    def __init__(self, x, y, z, id, idcha, opt):
        self.x = x
        self.y = y
        self.z = z
        self.id = id
        self.idcha = idcha
        self.opt = opt

    def printState(self):
        print(action[self.opt])
        print("X =", self.x, ", Y =", self.y, "Z =", self.z)


def PourXY(cur,   re):
    global tank_X
    global tank_Y
    if (cur.x > 0 and cur.y < tank_Y):
        re.x = cur.x - (tank_Y - cur.y)
        if (re.x < 0):
            re.x = 0
        re.y = cur.x + cur.y
        if (re.y > tank_Y):
            re.y = tank_Y
        re.z = cur.z
        return 1
    return 0


def PourXZ(cur,   re):
    global tank_X
    global tank_Y
    if (cur.x > 0 and cur.z < tank_Z):
        re.x = cur.x - (tank_Z - cur.z)
        if (re.x < 0):
            re.x = 0
        re.z = cur.x + cur.z
        if (re.z > tank_Z):
            re.z = tank_Z
        re.y = cur.y
        return 1
    return 0


def PourYX(cur,   re):
    global tank_X
    global tank_Y
    if (cur.y > 0 and cur.x < tank_X):
        re.y = cur.y - (tank_X - cur.x)
        if (re.y < 0):
            re.y = 0
        re.x = cur.x + cur.y
        if (re.x > tank_X):
            re.x = tank_X
        re.z = cur.z
        return 1

    return 0


def PourYZ(cur,   re):
    global tank_X
    global tank_Y
    if (cur.y > 0 and cur.z < tank_Z):
        re.y = cur.y - (tank_Z - cur.z)
        if (re.y < 0):
            re.y = 0
        re.z = cur.y + cur.z
        if (re.z > tank_Z):
            re.z = tank_Z
        re.x = cur.x
        return 1
    return 0


def PourZX(cur,   re):
    global tank_X
    global tank_Y
    if (cur.z > 0 and cur.x < tank_X):
        re.z = cur.z - (tank_X - cur.x)
        if (re.z < 0):
            re.z = 0
        re.x = cur.x + cur.z
        if (re.x > tank_X):
            re.x = tank_X
        re.y = cur.y
        return 1
    return 0


def PourZY(cur,   re):
    global tank_X
    global tank_Y
    if (cur.z > 0 and cur.y < tank_Y):
        re.z = cur.z - (tank_Y - cur.y)
        if (re.z < 0):
            re.z = 0
        re.y = cur.z + cur.y
        if (re.y > tank_Y):
            re.y = tank_Y
        re.x = cur.x
        return 1
    return 0


def call_operator(cur, re,  opt):
    if opt == 1:
        return PourXY(cur, re)
    if opt == 2:
        return PourXZ(cur, re)
    if opt == 3:
        return PourYX(cur, re)
    if opt == 4:
        return PourYZ(cur, re)
    if opt == 5:
        return PourZX(cur, re)
    if opt == 6:
        return PourZY(cur, re)


def goalCheck(state):
    global goal
    return state.x == goal or state.y == goal or state.z == goal


def findState(state, stack):
    for i in range(0, len(stack)):
        node = stack[i]
        if state.x == node.x and state.y == node.y and state.z == node.z:
            return 1
    return 0


def BFS_Algorithm(state):
    global id
    global open
    global close
    open.append(state)
    while len(open) != 0:
        node = open.pop(0)
        close.append(node)
        if goalCheck(node):
            return node

        for opt in range(1, 7):
            newNode = State(0, 0, 0, id, node.id, opt)
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
    state = State(10, 0, 0, 0, 0, 0)
    id += 1
    node = BFS_Algorithm(state)
    if node == None:
        print("None")
    else:
        printGoal(node)
    quit()


if __name__ == "__main__":
    os.system("cls")
    main()
