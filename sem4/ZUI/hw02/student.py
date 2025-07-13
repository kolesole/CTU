from blockworld import BlockWorldEnv
import random
import numpy as np
import time

class QLearning():
	ALPHA = 0.8     # learning rate
	GAMMA = 0.9     # discount factor
	EPSILON = 0.99   # exploration rate

	def __init__(self, env: BlockWorldEnv):
		self.env = env
		self.Q = dict()   # Q-table

	# Update EPSILON
	def update_epsilon(self):
		self.EPSILON = max(self.EPSILON * 0.99999, 0.9)

	# Return an action based on EPSILON-greedy policy
	def choose_action(self, s):
		actions = s[0].get_actions()
		if random.random() < self.EPSILON:
			return random.choice(actions)         # exploration
		else:
			return self.get_max_arg_q(s)		  # exploitation

	# Return the maximum q for the state s
	def get_max_q(self, s):
		actions = s[0].get_actions()
		return np.max([self.Q.get((s, a), 0) for a in actions])

	# Return which maximize the q for the state s
	def get_max_arg_q(self, s):
		actions = s[0].get_actions()
		return actions[np.argmax([self.Q.get((s, a), 0) for a in actions])]

	# Training function
	def train(self):
		episode_num = 0
		start_time = time.time()		# start of training
		while True:						# iterate between episodes
			episode_num += 1
			s, _ = self.env.reset()	    # reset the env
			while True:                 # iterate in the current episode
				act = self.choose_action(s)
				self.update_epsilon()
				key = (s, act)			# the key for Q-table
				s_, r, done, _, _ = self.env.step(act)		# take the action

				# Update Q[key]
				# Q[s, act] += alpha * (r + gamma * maxa(Q[s_, a]) - Q[s, act])
				self.Q[key] = (self.Q.get(key, 0) +
							   self.ALPHA * (r + self.GAMMA * self.get_max_q(s_) - self.Q.get(key, 0)))
				s = s_

				if done:	# end the episode if next_state == goal
					# self.EPSILON = 0.99
					break

				elapsed_time = time.time() - start_time
				if elapsed_time > 30:	       # end of training
					print(f"Number of episode: {episode_num}")
					return

	def act(self, s):
		return self.get_max_arg_q(s)

if __name__ == '__main__':
	# Here you can test your algorithm. Stick with N <= 4
	N = 4

	env = BlockWorldEnv(N)
	qlearning = QLearning(env)

	# Train
	# print('start training')
	qlearning.train()
	# print('finish training')

	# Evaluate
	test_env = BlockWorldEnv(N)

	test_problems = 1000
	solved = 0
	avg_steps: list[int] = []
	# results = []
	# for i in range(100):

	for test_id in range(test_problems):
		s, _ = test_env.reset()
		done = False

		print(f"\nProblem {test_id}:")
		print(f"{s[0]} -> {s[1]}")

		for step in range(50): 	# max 50 steps per problem
			a = qlearning.act(s)
			s_, r, done, truncated, _ = test_env.step(a)

			print(f"{a}: {s[0]}")

			s = s_

			if done:
				solved += 1
				avg_steps.append(step + 1)
				break

	avg_step = sum(avg_steps) / len(avg_steps)
	print(f"Solved {solved}/{test_problems} problems, with average number of steps {avg_step}.")