
import os

action = ["First action", "Chuyen 1 tu si A->B", "Chuyen 2 tu si A->B",
          "Chuyen 1 con quy A->B", "Chuyen 2 con quy A->B", "Chuyen 1 tu si va 1 con quy A->B",
          "Chuyen 1 tu si B->A", "Chuyen 2 tu si B->A", "Chuyen 1 con quy B->A",
          "Chuyen 2 con quy B->A", "Chuyen 1 tu si va 1 con quy B->A"]


id = 0
open = []
close = []


class State:
    def __init__(self, si, quy, vt, id, idcha, opt):
        self.si = si
        self.quy = quy
        self.vt = vt
        self.id = id
        self.idcha = idcha
        self.opt = opt

    def printState(self):
        print(action[self.opt])
        print("Tu Si:", self.si, ",Con Quy:",
              self.quy, ", Vi Tri Bo:", self.vt)


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


def goalCheck(state):
    return state.si == 0 and state.quy == 0 and state.vt == 'B'


def checkOver(cur):
    if (cur.si == cur.quy):
        return 1
    if (cur.si == 0 or cur.si == 3):
        return 1
    return 0


def AB1S(cur, re):
    if (cur.si >= 1):
        re.si = cur.si - 1
        re.quy = cur.quy
        re.vt = 'B'
        if (checkOver(re)):
            return 1
    return 0


def AB2S(cur, re):
    if (cur.si >= 2):
        re.si = cur.si - 2
        re.quy = cur.quy
        re.vt = 'B'
        if (checkOver(re)):
            return 1
    return 0


def AB1Q(cur, re):
    if (cur.quy >= 1):
        re.si = cur.si
        re.quy = cur.quy - 1
        re.vt = 'B'
        if (checkOver(re)):
            return 1
    return 0


def AB2Q(cur, re):
    if (cur.quy >= 2):
        re.si = cur.si
        re.quy = cur.quy - 2
        re.vt = 'B'
        if (checkOver(re)):
            return 1
    return 0


def AB1S1Q(cur, re):
    if (cur.quy >= 1 and cur.si >= 1):
        re.si = cur.si - 1
        re.quy = cur.quy - 1
        re.vt = 'B'
        if (checkOver(re)):
            return 1
    return 0


def BA1S(cur, re):
    if ((3-cur.si) >= 1):
        re.si = cur.si + 1
        re.quy = cur.quy
        re.vt = 'A'
        if (checkOver(re)):
            return 1
    return 0


def BA2S(cur, re):
    if ((3-cur.si) >= 2):
        re.si = cur.si + 2
        re.quy = cur.quy
        re.vt = 'A'
        if (checkOver(re)):
            return 1
    return 0


def BA1Q(cur, re):
    if ((3-cur.quy) >= 1):
        re.si = cur.si
        re.quy = cur.quy + 1
        re.vt = 'A'
        if (checkOver(re)):
            return 1
    return 0


def BA2Q(cur, re):
    if ((3-cur.quy) >= 2):
        re.si = cur.si
        re.quy = cur.quy + 2
        re.vt = 'A'
        if (checkOver(re)):
            return 1
    return 0


def BA1S1Q(cur, re):
    if ((3-cur.quy) >= 1 and (3-cur.si) >= 1):
        re.si = cur.si + 1
        re.quy = cur.quy + 1
        re.vt = 'A'
        if (checkOver(re)):
            return 1
    return 0


def call_operator(cur, re, opt):
    if (cur.vt == 'A'):
        if opt == 1:
            return AB1S(cur, re)
        if opt == 2:
            return AB2S(cur, re)
        if opt == 3:
            return AB1Q(cur, re)
        if opt == 4:
            return AB2Q(cur, re)
        if opt == 5:
            return AB1S1Q(cur, re)

    elif (cur.vt == 'B'):
        if opt == 6:
            return BA1S(cur, re)
        if opt == 7:
            return BA2S(cur, re)
        if opt == 8:
            return BA1Q(cur, re)
        if opt == 9:
            return BA2Q(cur, re)
        if opt == 10:
            return BA1S1Q(cur, re)
    return 0


def findState(state, stack):
    for i in range(0, len(stack)):
        node = stack[i]
        if state.si == node.si and state.quy == node.quy and state.vt == node.vt:
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

        for opt in range(1, 11):
            newNode = State(0, 0, 0, id, node.id, opt)
            id += 1
            if call_operator(node, newNode, opt):
                if findState(newNode, open) or findState(newNode, close):
                    continue
                open.append(newNode)
    return None


def main():
    global id
    state = State(3, 3, 'A', 0, 0, 0)
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
