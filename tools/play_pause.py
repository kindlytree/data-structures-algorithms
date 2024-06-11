import pygame
import os

# 初始化Pygame
pygame.init()

# 设置屏幕大小
screen = pygame.display.set_mode((640, 480))

# 设置视频文件路径
video_path = os.path.join("media", "videos", "quick_sort_visualization", "480p15", "QuickSortVisualization.mp4")

# 创建视频对象
movie = pygame.movie.Movie(video_path)

# 设置视频播放窗口
movie_screen = pygame.Surface(movie.get_size()).convert()

# 设置播放区域
screen = pygame.display.set_mode(movie.get_size())

# 播放视频
movie.set_display(screen)
movie.play()

# 主循环
running = True
paused = False
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                if paused:
                    movie.play()
                else:
                    movie.pause()
                paused = not paused

    pygame.display.update()

# 退出Pygame
pygame.quit()
