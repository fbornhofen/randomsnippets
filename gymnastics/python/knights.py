#!/usr/bin/env python
from math import fabs, floor 

SIZE=8

def knight_moves(pos):
    x = pos[0]
    y = pos[1]
    return [(i,j) for i in range(SIZE) for j in range(SIZE) if
                i == x + 2 and j == y + 1 or
                i == x + 2 and j == y - 1 or
                i == x + 1 and j == y + 2 or
                i == x + 1 and j == y - 2 or
                i == x - 1 and j == y + 2 or
                i == x - 1 and j == y - 2 or
                i == x - 2 and j == y + 1 or
                i == x - 2 and j == y - 1]

def knights(start, visited, solutions):
    moves = knight_moves(start)
    visited = visited[:]
    visited.append(start)
    if len(visited) == SIZE*SIZE:
        return visited

    for m in moves:
        if not m in visited:
            tmp = knights(m, visited, solutions)
            if len(tmp) == SIZE*SIZE:
                solutions.append(tmp)
                print tmp
    return []

def valid_move(frm, to):
    return floor(fabs(to[0]-frm[0])) == 2 and \
           floor(fabs(to[1]-frm[1])) == 1 or \
           floor(fabs(to[0]-frm[0])) == 1 and \
           floor(fabs(to[1]-frm[1])) == 2

def validate(moves):
    prev = moves[0]
    for move in moves[1:]:
        if not valid_move(prev, move):
            return False
        prev = move
    return True

if __name__ == "__main__":
    solutions = []
    res = knights((0,0), [], solutions)
    for s in solutions:
        print len(s)
        print s
        print validate(s)

