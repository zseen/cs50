from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""
    rows = len(a) + 1
    columns = len(b) + 1
    cost = [[(0, None)] * columns for i in range(rows)]

    for row in range(1, rows):
        cost[row][0] = (row, Operation.DELETED)
    for column in range(1, columns):
        cost[0][column] = (column, Operation.INSERTED)

    for i in range(1, rows):
        for j in range(1, columns):
            deletionCost = cost[i-1][j]
            insertionCost = cost[i][j-1]
            substitutionCost = cost[i-1][j-1]

            substCost = substitutionCost[0]
            if a[i - 1] == b[j - 1]:
                minCost = min(deletionCost[0] + 1, insertionCost[0] + 1, substCost)
            else:
                substCost += 1
                minCost = min(deletionCost[0] + 1, insertionCost[0] + 1, substCost)

            if minCost == deletionCost[0] + 1:
                cost[i][j] = (deletionCost[0] + 1, Operation.DELETED)
            elif minCost == insertionCost[0] + 1:
                cost[i][j] = (insertionCost[0] + 1, Operation.INSERTED)
            else:
                cost[i][j] = (substCost, Operation.SUBSTITUTED)

    return cost
