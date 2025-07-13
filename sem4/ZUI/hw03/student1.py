import random, time
import math
import numpy as np

import ox

class MCTSNode:
    def __init__(self, board, parent=None, action=None):
        self.board = board
        self.parent = parent
        self.action = action  # Action that led to this node
        self.children = {}    # Map from action to MCTSNode
        self.visits = 0       # Number of visits to this node
        self.value = 0.0      # Total value (wins) from simulations through this node
        self.untried_actions = list(board.get_actions())  # Actions not yet expanded
        self.player = board.current_player()  # Player who will make the next move

    def select_child(self, exploration_weight=1.41):
        """
        Use UCB1 formula to select a child node
        """
        log_n_visits = math.log(self.visits)
        
        def ucb(child):
            exploitation = child.value / child.visits
            exploration = exploration_weight * math.sqrt(log_n_visits / child.visits)
            return exploitation + exploration
        
        return max(self.children.values(), key=ucb)

    def expand(self):
        """
        Expand by randomly selecting an untried action and adding a child node
        """
        if not self.untried_actions:
            return None  # No untried actions

        action = random.choice(self.untried_actions)
        self.untried_actions.remove(action)
        
        # Create a new board with the action applied
        next_board = self.board.clone()
        next_board.apply_action(action)
        
        # Create a child node
        child = MCTSNode(next_board, parent=self, action=action)
        self.children[action] = child
        return child

    def is_fully_expanded(self):
        """
        Check if all possible actions from this node have been expanded
        """
        return len(self.untried_actions) == 0

    def is_terminal(self):
        """
        Check if this node represents a terminal state
        """
        return self.board.is_terminal()

    def backpropagate(self, result):
        """
        Update node statistics from simulation result
        """
        self.visits += 1
        # Update value based on the perspective of the player who made the move leading to this node
        if self.parent:
            player_perspective = 1 - self.player  # Parent's perspective
            result_for_parent = result[player_perspective]
            self.value += result_for_parent
        else:
            # For root node, update from current player's perspective
            self.value += result[self.player]
            
        # Propagate up the tree
        if self.parent:
            self.parent.backpropagate(result)

    def best_child(self, exploration_weight=0.0):
        """
        Return the best child based only on exploitation (for final move selection)
        """
        if exploration_weight == 0:
            # Pure exploitation - select child with highest win rate
            return max(self.children.values(), 
                       key=lambda c: c.value / c.visits if c.visits > 0 else 0)
        else:
            # Use UCB1 for selection with exploration
            return self.select_child(exploration_weight)


class MCTSBot1:
    def __init__(self, play_as: int, time_limit: float):
        self.play_as = play_as
        self.time_limit = time_limit * 0.9
        
    def play_action(self, board):
        """
        Implement MCTS bot to select the best action
        """
        root = MCTSNode(board.clone())
        
        start_time = time.time()
        num_simulations = 0
        
        # Run MCTS iterations until time limit
        while (time.time() - start_time) < self.time_limit:
            # 1. Selection: traverse the tree to find a node to expand
            node = root
            while not node.is_terminal() and node.is_fully_expanded():
                node = node.select_child()
            
            # 2. Expansion: if node is not terminal and has untried actions, expand it
            if not node.is_terminal() and not node.is_fully_expanded():
                node = node.expand()
            
            # 3. Simulation: play out a random game from this node
            if node:  # node could be None if expansion failed
                simulation_board = node.board.clone()
                
                # Simulate random play until the game ends
                while not simulation_board.is_terminal():
                    available_actions = list(simulation_board.get_actions())
                    action = random.choice(available_actions)
                    simulation_board.apply_action(action)
                
                # 4. Backpropagation: update statistics up the tree
                result = simulation_board.get_rewards()
                node.backpropagate(result)
                
                num_simulations += 1
        
        # Select the best action based on highest visit count
        if not root.children:
            # If no simulations were completed, choose randomly
            return random.choice(list(board.get_actions()))
        
        best_action = max(root.children.items(), 
                          key=lambda item: item[1].visits)[0]
        
        return best_action


if __name__ == '__main__':
    board = ox.Board(8)  # 8x8
    bots = [MCTSBot1(0, 0.1), MCTSBot1(1, 1.0)]

    # try your bot against itself
    while not board.is_terminal():
        current_player = board.current_player()
        current_player_mark = ox.MARKS_AS_CHAR[ ox.PLAYER_TO_MARK[current_player] ]

        current_bot = bots[current_player]
        a = current_bot.play_action(board)
        board.apply_action(a)

        print(f"{current_player_mark}: {a} -> \n{board}\n")