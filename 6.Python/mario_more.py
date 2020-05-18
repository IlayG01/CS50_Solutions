def recursive_pyramid(height, space=0):
	if height <= 0:
		return
	else:
		recursive_pyramid(height-1, space+1)
		print(' ' * (space) + '#' * height + "  " + '#' * height)
			  

def main():
	while True:
		try:
			number = int(input("whatt is your number? "))
		except ValueError:
			continue
		if number > 0 and number < 9:
			break

	recursive_pyramid(number)

main()