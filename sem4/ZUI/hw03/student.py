import random, time
import numpy as np

import student1 as pavel_huesosov

import ox

class MCTSBot:
	C = np.sqrt(2)

	def __init__(self, play_as: int, time_limit: float):
		self.play_as = play_as
		self.time_limit = time_limit * 0.9
		self.Q = dict()
		self.action_N = dict()
		self.N = dict()

	# Method selects an action
	def select_action(self, board):
		best_action = None
		best_value = -np.inf
		expanded = False
		for a in board.get_actions():
			cur_action_n = self.action_N.get((board, a), 0)
			if cur_action_n == 0:
				best_action = a
				expanded = True
				break

			cur_value = self.Q.get((board, a)) + self.C * np.sqrt(np.log(self.N.get(board)) / cur_action_n)

			if cur_value > best_value:
				best_value = cur_value
				best_action = a

		return best_action, expanded

	# Method simulates the game
	def simulate(self, board):
		board_copy = board.clone()
		while not board_copy.is_terminal():
			random_a = random.choice(list(board_copy.get_actions()))
			board_copy.apply_action(random_a)

		return board_copy.get_rewards()[self.play_as]

	# Method explores and exploits(with UCB)
	def select_backpropagate(self, board):
		self.N[board] = self.N.get(board, 0) + 1

		if board.is_terminal():
			return board.get_rewards()[self.play_as]

		best_action, expanded = self.select_action(board)
		board_copy = board.clone()
		board_copy.apply_action(best_action)

		self.action_N[(board, best_action)] = self.action_N.get((board, best_action), 0) + 1

		if expanded:
			reward = self.simulate(board_copy)
			self.N[board_copy] = self.N.get(board_copy, 0) + 1
		else:
			reward = self.select_backpropagate(board_copy)

		cur_value = self.Q.get((board, best_action), 0)
		cur_action_n = self.action_N.get((board, best_action))
		self.Q[(board, best_action)] = cur_value + (reward - cur_value) / cur_action_n

		return reward

	# Method selects the best action
	def select_best_action(self, board):
		best_action = None
		best_value = -np.inf
		for a in board.get_actions():
			board_copy = board.clone()
			board_copy.apply_action(a)
			if board_copy.is_terminal():
				return a
			cur_value = self.Q.get((board, a), 0)
			if cur_value > best_value:
				best_value = cur_value
				best_action = a
		return best_action

	def play_action(self, board):
		start_time = time.time()
		while (time.time() - start_time) < self.time_limit:
			self.select_backpropagate(board)

		return self.select_best_action(board)

if __name__ == '__main__':
	board = ox.Board(8)  # 8x8
	bots = [MCTSBot(0, 15), pavel_huesosov.MCTSBot1(1, 15)]
	# try your bot against itself
	while not board.is_terminal():
		current_player = board.current_player()
		current_player_mark = ox.MARKS_AS_CHAR[ ox.PLAYER_TO_MARK[current_player] ]

		current_bot = bots[current_player]
		a = current_bot.play_action(board)
		board.apply_action(a)

		print(f"{current_player_mark}: {a} -> \n{board}\n")
		if board.is_terminal():
			print(f"Winner: {board.winner}")


			