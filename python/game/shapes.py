import pygame

PINK = (255, 20, 147)
MOVING_IMAGE = 'baseball.png'
HORIZONTAL_VELOCITY = 3
VERTICAL_VELOCITY = 5

class Ball(pygame.sprite.Sprite):
    
    def __init__(self, x, y):
        super(Ball, self).__init__()
        self.image = pygame.image.load(MOVING_IMAGE).convert()
        self.image.set_colorkey(PINK)
        self.image = pygame.transform.scale_by(self.image, 0.1)
        
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y
        
        self.__vx = HORIZONTAL_VELOCITY
        self.__vy = VERTICAL_VELOCITY

    
    def update_v(self, vx, vy):
        self.__vx = vx
        self.__vy = vy
    
    
    def update_loc(self):
        self.rect.x += self.__vx
        self.rect.y += self.__vy
    

    def get_pos(self):
        return self.rect.x, self.rect.y
    
    
    def get_v(self):
        return self.__vx, self.__vy