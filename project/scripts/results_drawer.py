from PIL import Image, ImageDraw

im = Image.new('RGB', (2800, 2070), (128, 128, 128))
draw = ImageDraw.Draw(im)

with open("output.txt", "r") as file:
    lines = file.readlines()
    for rectangle_number, line in enumerate(lines[2:], 1):
        rectangle_data = [int(x) for x in line.strip().split()]
        rectangle_size = (rectangle_data[0], rectangle_data[1])
        rectangle_start = (rectangle_data[2], rectangle_data[3])

        should_rotate_rectangle = rectangle_data[4]
        if should_rotate_rectangle:
            rectangle_size = (rectangle_size[1], rectangle_size[0])

        print("{}: {}, {}".format(rectangle_number, rectangle_start, rectangle_size))

        if rectangle_start[0] != -1 and rectangle_start[1] != -1:
            draw.rectangle((rectangle_start[0], rectangle_start[1], (rectangle_start[0] + rectangle_size[0]), 
                (rectangle_start[1] + rectangle_size[1])), 
                fill = (0, 192, 192), outline = (255, 255, 255))

im.save('res.png', quality=100)