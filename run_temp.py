from main_temp import LivePlot
import argparse
import serial


#
arg_save = None
arg_clear = False
arg_only_txt = False

parser = argparse.ArgumentParser(
    description="""UI for Temperature logging. Running this script without any args, will give a live plot and values in the terminal"""
)

parser.add_argument("-t", "--txt", help="only saving data to txt (NO PLOT). ",
                    action="store_true")

parser.add_argument("-s", "--save", help="Save data to the data.txt file",
                    action="store_true")

parser.add_argument("-d", "--default", help="Clear data from data.txt and save data to data.txt ",
                    action="store_true")

args = parser.parse_args()


if args.save:
	arg_save = "data.txt"

if args.default:
	arg_clear = True
	arg_save = "data.txt"

if args.txt:
	arg_only_txt = True
	arg_save = "data.txt"

if __name__ == '__main__':    
	device = serial.Serial(port='/dev/tty.usbmodem1411', baudrate=9600) # R_Pi = /dev/ttyACM0 
	p = LivePlot(device, float, verb=False,save=arg_save, clear=arg_clear, only_txt= arg_only_txt)
	p.start()
	raw_input()
	p.join()
