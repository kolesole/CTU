class MyPlayer:
    '''Class MyPlayer with tactics: each field has its own importance'''
    def __init__(self, my_color, opponent_color):
        self.name = 'kolesole'
        self.my_color = my_color
        self.opponent_color = opponent_color

    def move(self, board):
        self.board = board
        possible_moves = []                                                       #list with all possible moves
        importance_moves = []                                                     #list with the importance of every move
        turned_chips = []                                                         #list with the number of turned chips for each possible move
        best_moves = [(0, 0), (0, 7), (7, 7), (7, 0)]                             #list with the most important fields
        good_moves = [(0, 1), (0, 2), (0, 3), (0, 4), (0, 5), (0, 6), (1, 7), (2, 7), (3, 7), (4, 7), (5, 7), (6, 7),  #list with the good fields
                      (7, 6), (7, 5), (7, 4), (7, 3), (7, 2), (7, 1), (6, 0), (5, 0), (4, 0), (3, 0), (2, 0), (1, 0)]
        most_dangerous_moves = [(1, 1), (1, 6), (6, 6), (6, 1)]                   #list with the most dangerous fields
        dangerous_moves = [(1, 2), (1, 3), (1, 4), (1, 5), (2, 6), (3, 6), (4, 6), (5, 6), (6, 5), (6, 4), (6, 3),    #list with the dangerous fields
                           (6, 2), (5, 1), (4, 1), (3, 1), (2, 1)]
        neutral_moves = [(2, 2), (2, 3), (2, 4), (2, 5), (3, 5), (4, 5), (5, 5), (5, 4), (5, 3), (5, 2), (4, 2), (3, 2)]   #list with the neutral fields
        for raw in range(8):                                                   #cycle that is responsible for horizontal moves from left to right
            for column in range(6):
                if self.board[raw][column] == self.my_color:
                    if self.board[raw][column + 1] == self.opponent_color:
                        for k in range(column + 1, 7):
                            if self.board[raw][k + 1] == self.my_color:
                                break
                            if self.board[raw][k + 1] != self.opponent_color and self.board[raw][k + 1] != self.my_color:
                                possible_moves.append((raw, k + 1))            #adding all possible moves to the list
                                turned_chips.append(k + 1 - column - 1)        #adding the number of chips turned over for move
                                break
        for raw in range(8):                                                   #cycle that is responsible for horizontal moves from right to left
            for column in range(7, 1, -1):
                if self.board[raw][column] == self.my_color:
                    if self.board[raw][column - 1] == self.opponent_color:
                        for k in range(column - 1, 0, -1):
                            if self.board[raw][k - 1] == self.my_color:
                                break
                            if self.board[raw][k - 1] != self.opponent_color and self.board[raw][k - 1] != self.my_color:
                                possible_moves.append((raw, k - 1))             #adding all possible moves to the list
                                turned_chips.append(column - (k - 1) - 1)       #adding the number of chips turned over for move
                                break
        for column in range(8):                                                 #cycle that is responsible for vertical moves from top to bottom
            for raw in range(6):
                if self.board[raw][column] == self.my_color:
                    if self.board[raw + 1][column] == self.opponent_color:
                        for k in range(raw + 1, 7):
                            if self.board[k + 1][column] == self.my_color:
                                break
                            if self.board[k + 1][column] != self.opponent_color and self.board[k + 1][column] != self.my_color:
                                possible_moves.append((k + 1, column))          #adding all possible moves to the list
                                turned_chips.append(k + 1 - raw - 1)            #adding the number of chips turned over for move
                                break
        for column in range(8):                                                 #cycle that is responsible for vertical moves from bottom to top
            for raw in range(7, 1, -1):
                if self.board[raw][column] == self.my_color:
                    if self.board[raw - 1][column] == self.opponent_color:
                        for k in range(raw - 1, 0, -1):
                            if self.board[k - 1][column] == self.my_color:
                                break
                            if self.board[k - 1][column] != self.opponent_color and self.board[k - 1][column] != self.my_color:
                                possible_moves.append((k - 1, column))         #adding all possible moves to the list
                                turned_chips.append(raw - (k - 1) - 1)         #adding the number of chips turned over for move
                                break
        for raw in range(6):                                                   #cycle that is responsible for diagonal moves from the upper left corner to the lower right
            for column in range(6):
                if self.board[raw][column] == self.my_color:
                    if self.board[raw + 1][column + 1] == self.opponent_color:
                        r, cl = raw + 1, column + 1
                        while r != 7 and cl != 7:
                            if self.board[r + 1][cl + 1] == self.my_color:
                                break
                            if self.board[r + 1][cl + 1] != self.opponent_color and self.board[r + 1][cl + 1] != self.my_color:
                                possible_moves.append((r + 1, cl + 1))       #adding all possible moves to the list
                                turned_chips.append(r + 1 - raw - 1)         #adding the number of chips turned over for move
                                break
                            else:
                                r += 1
                                cl += 1
        for raw in range(2, 8):                                                #cycle that is responsible for diagonal moves from the lower left corner to the upper right
            for column in range(0, 6):
                if self.board[raw][column] == self.my_color:
                    if self.board[raw - 1][column + 1] == self.opponent_color:
                        r, cl = raw - 1, column + 1
                        while r != 0 and cl != 7:
                            if self.board[r - 1][cl + 1] == self.my_color:
                                break
                            if self.board[r - 1][cl + 1] != self.opponent_color and self.board[r - 1][cl + 1] != self.my_color:
                                possible_moves.append((r - 1, cl + 1))         #adding all possible moves to the list
                                turned_chips.append(r + 1 - column - 1)        #adding the number of chips turned over for move
                                break
                            else:
                                r -= 1
                                cl += 1
        for raw in range(0, 6):                                                 #cycle that is responsible for diagonal moves from the upper right corner to the lower left
            for column in range(2, 8):
                if self.board[raw][column] == self.my_color:
                    if self.board[raw + 1][column - 1] == self.opponent_color:
                        r, cl = raw + 1, column - 1
                        while r != 7 and cl != 0:
                            if self.board[r + 1][cl - 1] == self.my_color:
                                break
                            if self.board[r + 1][cl - 1] != self.opponent_color and self.board[r + 1][cl - 1] != self.my_color:
                                possible_moves.append((r + 1, cl - 1))           #adding all possible moves to the list
                                turned_chips.append(r + 1 - raw - 1)             #adding the number of chips turned over for move
                                break
                            else:
                                r += 1
                                cl -= 1
        for raw in range(2, 8):                                                  #cycle that is responsible for diagonal moves form the lower right corner to the upper left
            for column in range(2, 8):
                if self.board[raw][column] == self.my_color:
                    if self.board[raw - 1][column - 1] == self.opponent_color:
                        r, cl = raw - 1, column - 1
                        while r != 0 and cl != 0:
                            if self.board[r - 1][cl - 1] == self.my_color:
                                break
                            if self.board[r - 1][cl - 1] != self.opponent_color and self.board[r - 1][cl - 1] != self.my_color:
                                possible_moves.append((r - 1, cl - 1))           #adding all possible moves to the list
                                turned_chips.append(column - (cl - 1) - 1)       #adding the number of chips turned over for move
                                break
                            else:
                                r -= 1
                                cl -= 1
        if possible_moves == []:                                                 #if there are no possible moves
            return None                                                          #the player returns None
        for i in range(len(possible_moves)):                                     #cycle during which the importance of each possible move and the number of tiles turned over for that move are summed up
            if possible_moves[i] in best_moves:
                importance_moves.append(100 + turned_chips[i])
            elif possible_moves[i] in good_moves:
                importance_moves.append(50 + turned_chips[i])
            elif possible_moves[i] in most_dangerous_moves:
                importance_moves.append(-100 + turned_chips[i])
            elif possible_moves[i] in dangerous_moves:
                importance_moves.append(-50 + turned_chips[i])
            elif possible_moves[i] in neutral_moves:
                importance_moves.append(0 + turned_chips[i])
        for i in range(len(possible_moves)):                                      #cycle that finds identical possible moves and summarizes their importance
            for j in range(1, len(possible_moves)):
                if possible_moves[i] == possible_moves[j]:
                    importance_moves[i] += importance_moves[j]
        return possible_moves[importance_moves.index(max(importance_moves))]









