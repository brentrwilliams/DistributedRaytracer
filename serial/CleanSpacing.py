import sys

def main():
   with open(sys.argv[1], 'r') as f:
      while True:
         c = f.read(1)
         if not c:
            break
         if c != '\r':
            sys.stdout.write(c)

if __name__ == '__main__':
   main()
