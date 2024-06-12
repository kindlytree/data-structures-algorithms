from manim import *

class QuickSortVisualization(Scene):
    def quicksort(self, array, start, end):
        if start >= end:
            return

        pivot_index = self.partition(array, start, end)
        self.wait(1)  # 暂停1秒
        self.quicksort(array, start, pivot_index - 1)
        self.wait(1)  # 暂停1秒
        self.quicksort(array, pivot_index + 1, end)

    def partition(self, array, start, end):
        pivot_index = start
        pivot_value = array[end]
        pivot_label = self.create_label(end, "Pivot", UP, 'red')
        index_label = self.create_label(start, "pivot_index", DOWN, 'red')
        i_label = self.create_label(start, "i", UP, 'yellow')
        self.add(pivot_label)
        self.add(index_label)
        self.add(i_label)
        
        low_arrow = self.create_arrow(pivot_index, "DOWN", DOWN, RED)
        high_arrow = self.create_arrow(end, "UP", UP, YELLOW)
        self.add(low_arrow, high_arrow)
        
        for i in range(start, end):
            high_arrow.next_to(self.bars[i], UP)
            i_label.next_to(self.bars[i], UP+np.array((0, -0.7, 0.0)))
            self.wait(0.5)
            if array[i] < pivot_value: #第一次的时候是第一个元素和最后一个比较，如果比最后一个要小，其实没有发生置换（因为i和pivot_value的值相等），但pivot_index会加1，只要后面有一次array[i]比pivot值要大，这时跳过，pivot_index处保留了较大的值
                array[i], array[pivot_index] = array[pivot_index], array[i]
                self.swap_bars(i, pivot_index)
                pivot_index += 1
                low_arrow.next_to(self.bars[pivot_index], DOWN)
                index_label.next_to(self.bars[pivot_index], DOWN)
        
        array[pivot_index], array[end] = array[end], array[pivot_index]
        self.swap_bars(pivot_index, end)
        self.remove(pivot_label, low_arrow, high_arrow, index_label, i_label)
        
        return pivot_index

    def swap_bars(self, i, j):
        if i != j:
            self.play(Swap(self.bars[i], self.bars[j]))
            self.bars[i], self.bars[j] = self.bars[j], self.bars[i]
        for bar in self.bars:
            bar.align_to(DOWN, DOWN)
        self.wait(1)  # 暂停1秒

    def construct(self):
        array = [7, 2, 5, 3, 6, 4, 1]
        self.bars = self.create_bars(array)
        for bar in self.bars:
            bar.align_to(DOWN, DOWN)
        self.play(*[Create(bar) for bar in self.bars])
        self.wait(1)
        self.quicksort(array, 0, len(array) - 1)

    def create_bars(self, array):
        bars = []
        for i, value in enumerate(array):
            bar = self.create_bar(value)
            bar.move_to(RIGHT * i + DOWN)
            bars.append(bar)
        
        # 对齐所有的VGroup的底部
        group = VGroup(*bars)
        group.center()  # 将整个组居中
        return bars

    def create_bar(self, value):
        bar_height = value * 0.5
        bar = VGroup()
        rectangle = Rectangle(
            width=0.6, height=bar_height,
            fill_color=BLUE, fill_opacity=0.75,
            stroke_color=WHITE
        )
        number = Text(str(value), color=WHITE, font_size=24)
        number.move_to(rectangle.get_center())
        bar.add(rectangle, number)
        return bar
    
    def create_label(self, index, text, direction, color_str):
        label = Text(text, color = RED if color_str == 'red' else YELLOW, font_size=24)
        label.next_to(self.bars[index], direction)
        return label

    def create_arrow(self, index, dic_str, direction, color):
        arrow = Arrow(start=UP if dic_str == "UP" else DOWN, end=UP if dic_str == "DOWN" else DOWN, color=color)
        arrow.next_to(self.bars[index], direction)
        return arrow

if __name__ == "__main__":
    scene = QuickSortVisualization()
    scene.render()

# 渲染命令：在终端中运行
# manim -pql quicksort_manim.py QuickSortVisualization
# pydub\utils.py:170: RuntimeWarning: Couldn't find ffmpeg or avconv - defaulting to ffmpeg, but may not work
# https://www.gyan.dev/ffmpeg/builds/
# https://www.gyan.dev/ffmpeg/builds/packages/ffmpeg-2024-06-06-git-d55f5cba7b-essentials_build.7z
# wget https://repo.anaconda.com/archive/Anaconda3-2023.03-Linux-x86_64.sh
# wsl中安装linux，windows平台中的vscode安装remote -wsl扩展
# wsl中anaconda安装在/home/username/anaconda3中  # Add Anaconda to PATH  nano ~/.zshrc
# export PATH="$HOME/anaconda3/bin:$PATH"  source ~/.zshrc
# manim -pql quick_sort_manim.py QuickSortVisualization