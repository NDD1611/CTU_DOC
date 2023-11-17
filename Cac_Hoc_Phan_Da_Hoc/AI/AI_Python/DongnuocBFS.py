EMPTY = 0
GOAL = 6
MAX_X = 9
MAX_Y = 4

action = ["First State", "Pour Water Full X", "Pour Water Full Y",
          "pour Water Empty X", "pour Water Empty Y", "pour Water X to Y", "pour Water Y to X"]


class State:
    def __init__(self):
        self.x = 0
        self.y = 0

    def display(self):
        print("X:", self.x, ",Y:", self.y)


def goalcheck(state):
    return state.x == GOAL or state.y == GOAL


def pourFullX(self, result):
    if (self.x < MAX_X):
        result.x = MAX_X
        result.y = self.y
        return True
    return False


def pourFullY(self, result):
    if (self.y < MAX_Y):
        result.x = self.x
        result.y = MAX_Y
        return True
    return False


def pourEmptyX(self, result):
    if (self.x > 0):
        result.x = EMPTY
        result.y = self.y
        return True
    return False


def pourEmptyY(self, result):
    if (self.y > 0):
        result.x = self.x
        result.y = EMPTY
        return True
    return False


def pourXtoY(self, result):
    if (self.x > 0 and self.y < MAX_Y):
        result.x = max(self.x - (MAX_Y - self.y), EMPTY)
        result.y = min(self.x + self.y, MAX_Y)
        return True
    return False


def pourYtoX(self, result):
    if (self.y > 0 and self.x < MAX_X):
        result.x = min(self.y + self.x, MAX_X)
        result.y = max(self.y - (MAX_X - self.x), EMPTY)
        return True
    return False


def callOperators(cur, result, option):
    if option == 1:
        return pourFullX(cur, result)
    if option == 2:
        return pourFullY(cur, result)
    if option == 3:
        return pourEmptyX(cur, result)
    if option == 4:
        return pourEmptyX(cur, result)
    if option == 5:
        return pourXtoY(cur, result)
    if option == 6:
        return pourYtoX(cur, result)
    else:
        print("Error while calling operators!")
        return False


def findState(state, stack):
    for i in range(0, len(stack)):
        node = stack[i]
        if state.x == node.state.x and state.y == node.state.y:
            return 1
    return 0


def BFS(state):
    OpenBFS = []
    CloseBFS = []
    root = Node(state, None, 0)
    OpenBFS.append(root)
    while len(OpenBFS) != 0:
        node = OpenBFS.pop()
        CloseBFS.append(node)
        if goalcheck(node.state):
            return node
        for opt in range(1, 7):
            newState = State()
            if callOperators(node.state, newState, opt):
                if findState(newState, CloseBFS) or findState(newState, OpenBFS):
                    continue
                newNode = Node(newState, node, opt)
                OpenBFS.append(newNode)
    return None


class Node:
    def __init__(self, state, parent, no_function):
        self.state = state
        self.parent = parent
        self.no_function = no_function

    def printNode(self):
        print(action[self.no_function])
        self.state.display()
        print("----------------------")


def printGoal(node):
    list = []
    while node.parent != None:
        list.append(node)
        node = node.parent
    list.append(node)

    while len(list) != 0:
        node1 = list.pop()
        node1.printNode()


def main():
    state = State()
    node = BFS(state)
    if node == None:
        print("none")
    else:
        printGoal(node)


main()
