from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


class ValueWithOperation:
    def __init__(self, value, operation):
        self.value = value
        self.operation = operation


def calculateValueAndOperationMatrix(a, b):
    numRows = len(a) + 1
    numColumns = len(b) + 1
    cost = [[ValueWithOperation(0, None)] * numColumns for i in range(numRows)]

    for row in range(1, numRows):
        cost[row][0] = ValueWithOperation(row, Operation.DELETED)
    for column in range(1, numColumns):
        cost[0][column] = ValueWithOperation(column, Operation.INSERTED)

    for j in range(1, numRows):
        for i in range(1, numColumns):
            deletionCost = cost[j - 1][i]
            insertionCost = cost[j][i - 1]
            substitutionCost = cost[j - 1][i - 1]

            if a[j - 1] == b[i - 1]:
                minCost = min(deletionCost.value + 1, insertionCost.value + 1, substitutionCost.value)
            else:
                substitutionCost.value += 1
                minCost = min(deletionCost.value + 1, insertionCost.value + 1, substitutionCost.value)

            if minCost == deletionCost.value + 1:
                cost[j][i] = ValueWithOperation(deletionCost.value + 1, Operation.DELETED)
            elif minCost == insertionCost.value + 1:
                cost[j][i] = ValueWithOperation(insertionCost.value + 1, Operation.INSERTED)
            else:
                cost[j][i] = ValueWithOperation(substitutionCost.value, Operation.SUBSTITUTED)

    return cost


def convertToTupleMatrix(valueAndOperationMatrix):
    matrixCopy = [row[:] for row in valueAndOperationMatrix]
    for j in range(0, len(matrixCopy)):
        for i in range(0, len(matrixCopy[0])):
            matrixCopy[j][i] = (valueAndOperationMatrix[j][i].value, valueAndOperationMatrix[j][i].operation)
    return matrixCopy


def distances(a, b):
    """Calculate edit distance from a to b"""
    valueAndOperationMatrix = calculateValueAndOperationMatrix(a, b)
    return convertToTupleMatrix(valueAndOperationMatrix)
