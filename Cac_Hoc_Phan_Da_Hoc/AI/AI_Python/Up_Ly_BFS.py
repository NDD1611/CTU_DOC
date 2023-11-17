import os
os.system("cls")

open = []
close = []
id = 0

action = ["First action", "UP 1 2 3", "UP 2 3 4", "UP 3 4 5", "UP 4 5 6"]


class State:
    def __init__(self, vt1, vt2, vt3, vt4, vt5, vt6, id, idcha, opt):
        self.vt1 = vt1
        self.vt2 = vt2
        self.vt3 = vt3
        self.vt4 = vt4
        self.vt5 = vt5
        self.vt6 = vt6
        self.id = id
        self.idcha = idcha
        self.opt = opt

    def printState(self):
        print(action[self.opt])
        print(self.vt1, self.vt2, self.vt3, self.vt4, self.vt5, self.vt6)


def goalCheck(s):
    return s.vt1 == 1 and s.vt2 == 1 and s.vt3 == 1 and s.vt4 == 1 and s.vt5 == 1 and s.vt6 == 1


def A123(cur,  re):
    re.vt1 = -cur.vt1
    re.vt2 = -cur.vt2
    re.vt3 = -cur.vt3
    re.vt4 = cur.vt4
    re.vt5 = cur.vt5
    re.vt6 = cur.vt6
    return 1


def A234(cur,  re):
    re.vt1 = cur.vt1
    re.vt2 = -cur.vt2
    re.vt3 = -cur.vt3
    re.vt4 = -cur.vt4
    re.vt5 = cur.vt5
    re.vt6 = cur.vt6
    return 1


def A345(cur,  re):
    re.vt1 = cur.vt1
    re.vt2 = cur.vt2
    re.vt3 = -cur.vt3
    re.vt4 = -cur.vt4
    re.vt5 = -cur.vt5
    re.vt6 = cur.vt6
    return 1


def A456(cur,  re):
    re.vt1 = cur.vt1
    re.vt2 = cur.vt2
    re.vt3 = cur.vt3
    re.vt4 = -cur.vt4
    re.vt5 = -cur.vt5
    re.vt6 = -cur.vt6
    return 1


def call_operator(cur,  re, opt):
    if opt == 1:
        return A123(cur, re)
    if opt == 2:
        return A234(cur, re)
    if opt == 3:
        return A345(cur, re)
    if opt == 4:
        return A456(cur, re)


def compareState(x, y):
    return x.vt1 == y.vt1 and x.vt2 == y.vt2 and x.vt3 == y.vt3 and x.vt4 == y.vt4 and x.vt5 == y.vt5 and x.vt6 == y.vt6


def findState(state, stack):
    for i in range(0, len(stack)):
        node = stack[i]
        if state.vt1 == node.vt1 and state.vt2 == node.vt2 and state.vt3 == node.vt3 and state.vt4 == node.vt4 and state.vt5 == node.vt5 and state.vt6 == node.vt6:
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

        for opt in range(1, 5):
            newNode = State(0, 0, 0, 0, 0, 0, id, node.id, opt)
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
    state = State(1, -1, 1, -1, 1, -1, 0, 0, 0)
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
