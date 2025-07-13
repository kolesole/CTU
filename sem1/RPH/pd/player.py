

COOPERATE = False
DEFECT = True
COOP = 0
DEF = 1

class MyPlayer:
    '''Class MyPlayer s pomerne jednoduchou a fungujici taktikou'''
    def __init__(self, payoff_matice, pocet_iteraci = 0):   # hlavni funke, ktera ma dva argumenty: matice a pocet
        self.payoff_matice = payoff_matice                     # iteraci(neni povinny)
        self.pocet_iteraci = int(pocet_iteraci)
        self.my_last_moves = [None]                         # vytvoreni dvou promen(my_last_moves a opponent_last_moves)
        self.opponent_last_moves = [None]

    def move(self):                                         # funkce, ktera zahrnuje herni strategii
        if 1 <= self.pocet_iteraci <= 4:
            if self.payoff_matice[COOP][COOP][0] + self.payoff_matice[COOP][DEF][0] >= self.payoff_matice[DEF][COOP][0] + \
                   self.payoff_matice[DEF][DEF][0]:
                return COOPERATE
            elif self.payoff_matice[COOP][COOP][0] + self.payoff_matice[COOP][DEF][0] < self.payoff_matice[DEF][COOP][0] + \
                    self.payoff_matice[DEF][DEF][0]:
                return DEFECT
        elif self.pocet_iteraci >= 5 or self.pocet_iteraci == 0:
            if self.opponent_last_moves[-1] == None:
                if self.payoff_matice[COOP][COOP][0] >= self.payoff_matice[DEF][DEF][0]:
                    return COOPERATE
                elif self.payoff_matice[COOP][COOP][0] < self.payoff_matice[DEF][DEF][0]:
                    return DEFECT
            elif self.opponent_last_moves[-1] == DEFECT:
                if self.payoff_matice[COOP][DEF][0] >= self.payoff_matice[DEF][DEF][0]:
                    return COOPERATE
                elif self.payoff_matice[COOP][DEF][0] < self.payoff_matice[DEF][DEF][0]:
                    return DEFECT
            elif self.opponent_last_moves[-1] == COOPERATE:
                if self.payoff_matice[COOP][COOP][0] >= self.payoff_matice[DEF][DEF][0]:
                    return COOPERATE
                elif self.payoff_matice[COOP][COOP][0] < self.payoff_matice[DEF][DEF][0]:
                    return DEFECT

    def record_last_moves(self, my_m, opp_m):                    #funkce, ktera vrati my_last_move a opponent_last_move
        self.my_last_moves.append(my_m)
        self.opponent_last_moves.append(opp_m)
        print("My last move:", my_m, "Opponent last move:", opp_m)









