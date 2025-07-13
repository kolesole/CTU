from blockworld import BlockWorld
from queue import PriorityQueue
from itertools import chain

# help function to find all blocks which are under each block
def get_blocks_under(state, num_blocks) -> list[list[int]]:
	under_state_blocks: list[list[int]] = [[] for _ in range(num_blocks)]

	for sublist in state:
		for i, val in enumerate(sublist):
			under_state_blocks[val - 1].extend(sublist[i + 1:])

	return under_state_blocks

class BlockWorldHeuristic(BlockWorld):
	num_blocks = None
	under_goal_blocks = None

	def __init__(self, num_blocks=5, state=None):
		BlockWorld.__init__(self, num_blocks, state)

	def heuristic(self, goal):
		self_state  = self.get_state()
		goal_state = goal.get_state()

		if BlockWorldHeuristic.num_blocks is None:               # if first func. call, define num_blocks and under_goal_blocks
			BlockWorldHeuristic.num_blocks = max(chain.from_iterable(goal_state))
			BlockWorldHeuristic.under_goal_blocks: list[list[int]] = get_blocks_under(goal_state, BlockWorldHeuristic.num_blocks)

		num_blocks = BlockWorldHeuristic.num_blocks                                     # copy num_blocks
		under_goal_blocks: list[list[int]] = BlockWorldHeuristic.under_goal_blocks      # copy under_goal_blocks
		under_state_blocks: list[list[int]] = get_blocks_under(self_state, num_blocks)  # find under_state_blocks

		heur = 0
		for s, g in zip(under_state_blocks, under_goal_blocks):    # compare under_state_blocks and under_goal_blocks
			heur += int(s != g)                                    # if sublists do not match heur++

		return heur

class AStar():
	def search(self, start, goal):
		opened_states: PriorityQueue[tuple[int, BlockWorld]] = PriorityQueue()
		# heuristics dictionary in which are infs. about closed and opened states(num_moves, heuristic, path)
		heuristics: dict[BlockWorld, tuple[int, int, list[int]]] = {}

		start_heur = start.heuristic(goal)
		heuristics[start] = (0, start_heur, [])
		opened_states.put((start_heur + 0, start))

		while not opened_states.empty():
			priority, cur_state = opened_states.get()
			cur_num_moves, cur_heur, cur_path = heuristics.get(cur_state)

			for action, neighbor in cur_state.get_neighbors():
				if neighbor.__eq__(goal):
					return cur_path + [action]

				neighbor_heur = None
				if neighbor in heuristics:                                                     # if neighbor is already closed or opened
					neighbor_num_moves, neighbor_heur, neighbor_path = heuristics[neighbor]    # copy inf. about neighbor
					if neighbor_num_moves <= cur_num_moves + 1:
						continue

				if neighbor_heur is None:                    # if neighbor is not closed or opened
					neighbor_heur = neighbor.heuristic(goal) # get new heuristic

				heuristics[neighbor] = (cur_num_moves + 1, neighbor_heur, cur_path + [action])
				opened_states.put((neighbor_heur + cur_num_moves + 1, neighbor))

		return None

if __name__ == '__main__':
	# Here you can test your algorithm. You can try different N values, e.g. 6, 7.
	N = 5

	start = BlockWorldHeuristic(N)
	goal = BlockWorldHeuristic(N)

	print("Searching for a path:")
	print(f"{start} -> {goal}")
	print()

	astar = AStar()
	path = astar.search(start, goal)

	if path is not None:
		print("Found a path:")
		print(path)

		print("\nHere's how it goes:")

		s = start.clone()
		print(s)

		for a in path:
			s.apply(a)
			print(s)

	else:
		print("No path exists.")

	print("Total expanded nodes:", BlockWorld.expanded)
