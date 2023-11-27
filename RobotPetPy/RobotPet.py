import socket

# network variables
robotIP = "127.0.0.1"
port = 4210
# don't change local IP
serverIP = "127.0.0.1"
# Create a UDP socket
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# Bind the socket to the port
server_address = (serverIP, port)
robot_address = (robotIP, port)
serverSocket.bind(server_address)
print("Do Ctrl+c to exit the program !!")

# Class for state machine
class robot:
    def __init__(self, name, state):
        # set variables 
        self.name = name
        self.state = state
        # Internal variables initial states
        self.sound = True
        self.sawApriltag = False
        self.aprilSeen = "dance"
        self.signSeen = "move"
        self.sawHuman = True
        self.stopLoop = False
        self.direction = "forward"

    def __str__(self):
        # class return str
        return f"{self.name}({self.state})"

    def sleep(self):
        self.state = "sleeping"
        print(self.name + " is " + self.state)
        if not self.stopLoop:
            if self.sound:
                print(self.name + " heard a sound!")
                self.stopLoop = True
                #send msg
                serverSocket.sendto(bytes('S', 'utf-8'), robot_address)
                self.search()

    def roam(self):
        self.state = "roaming"
        print(self.name + " is " + self.state)
        #send msg
        serverSocket.sendto(bytes('R', 'utf-8'), robot_address)

    def search(self):
        self.state = "searching"
        print(self.name + " is " + self.state)
        #send msg
        serverSocket.sendto(bytes('A', 'utf-8'), robot_address)
        if self.sawApriltag:
            print(self.name + " saw april tag: " + self.sawApriltag)
            match self.aprilSeen:
                case "roam":
                    self.roam()
                case "sleep":
                    self.sleep()
                case "dance":
                    self.search()
                case "move":
                    self.move()
        if self.sawHuman:
            print(self.name + " saw hand sign: " + self.signSeen)
            match self.signSeen:
                case "roam":
                    self.roam()
                case "sleep":
                    self.sleep()
                case "dance":
                    self.search()
                case "move":
                    self.move()

    def chaseBall(self):
        self.state = "chasing ball"
        print(self.name + " is " + self.state)
        #send msg
        serverSocket.sendto(bytes('S', 'utf-8'), robot_address)

    def eat(self):
        self.state = "eating"
        print(self.name + " is " + self.state)
        #send msg
        serverSocket.sendto(bytes('E', 'utf-8'), robot_address)

    def dance(self):
        self.state = "dancing"
        print(self.name + " is " + self.state)
        print("finished dancing!")
        #send msg
        serverSocket.sendto(bytes('D', 'utf-8'), robot_address)
        self.sleep()

    def move(self):
        self.state = "moving"
        print(self.name + " is " + self.state)
        #send msg
        serverSocket.sendto(bytes('M', 'utf-8'), robot_address)
        match self.direction:
                case "forward":
                    serverSocket.sendto(bytes('8', 'utf-8'), robot_address)
                case "left":
                    serverSocket.sendto(bytes('4', 'utf-8'), robot_address)
                case "right":
                    serverSocket.sendto(bytes('6', 'utf-8'), robot_address)
                case "backwards":
                    serverSocket.sendto(bytes('2', 'utf-8'), robot_address)
        print(self.name + " finished moving " + self.direction + "!")
        self.sleep()

# Initialize state machine
# (Name, State)
myRoboDog = robot("RoboDog1", "sleep")
print(myRoboDog)
# Start state machine
myRoboDog.sleep()
# receive UDP:
# serverSocket.recvfrom(port)
