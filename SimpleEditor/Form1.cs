using System;
using System.Drawing;
using System.Windows.Forms;

namespace SimpleEditor {
    public partial class Form1 : Form {
        public Form1() {
            InitializeComponent();

            MouseClick += Form1_MouseClick;
            Move += Form1_Move;
            Resize += Form1_Resize;
        }

        void ResizeWindow() { Size = new Size(gridWidth + 25, gridHeight + 100); }

        private void Form1_Resize(object sender, System.EventArgs e) { ResizeWindow(); }
        private void Form1_Move(object sender, System.EventArgs e) { }

        private void Form1_MouseClick(object sender, MouseEventArgs e) {
            if (tileMap != null) {
                if (e.X < gridWidth + paddingX && e.X > paddingX && e.Y < gridHeight + paddingY && e.Y > paddingY) {
                    if (tileMap[(e.X - paddingX) / (gridWidth / tileMap.GetLength(0)), (e.Y - paddingY) / (gridHeight / tileMap.GetLength(1))] == 0) {
                        GenerateTile((e.X - paddingX) / (gridWidth / divisionX) * (gridWidth / divisionX), (e.Y - paddingY) / (gridHeight / divisionY) * (gridHeight / divisionY), (gridWidth / divisionX), (gridHeight / divisionY), Color.Gray);
                        tileMap[(e.X - paddingX) / (gridWidth / divisionX), (e.Y - paddingY) / (gridHeight / divisionY)] = 1;
                    }
                    else {
                        GenerateTile((e.X - paddingX) / (gridWidth / divisionX) * (gridWidth / divisionX), (e.Y - paddingY) / (gridHeight / divisionY) * (gridHeight / divisionY), (gridWidth / divisionX), (gridHeight / divisionY), Color.White);
                        tileMap[(e.X - paddingX) / (gridWidth / divisionX), (e.Y - paddingY) / (gridHeight / divisionY)] = 0;
                    }
                }
            }
        }

        int[,] tileMap;
        static int gridWidth = 800, gridHeight = 800, divisionX, divisionY;
        static int paddingX = 10, paddingY = 75;
        private void button1_Click(object sender, System.EventArgs e) {
            divisionX = (int)numericUpDown1.Value;
            divisionY = (int)numericUpDown2.Value;

            ResizeWindow();
            GenerateGrid(gridWidth, gridHeight, divisionX, divisionY);
            tileMap = new int[divisionX, divisionY];
        }

        void GenerateTile(int x, int y, int width, int height, Color color) {
            CreateGraphics().FillRectangle(new SolidBrush(color), x + paddingX + 1, y + paddingY + 1, width - 1, height - 1);
        }

        void GenerateGrid(int width, int height, int divX, int divY) {
            gridWidth = width;
            gridHeight = height;

            CreateGraphics().Clear(Color.White);
            CreateGraphics().DrawLine(new Pen(Color.Black), paddingX, paddingY, width + paddingX, paddingY);
            CreateGraphics().DrawLine(new Pen(Color.Black), paddingX, paddingY, paddingX, height + paddingY);
            CreateGraphics().DrawLine(new Pen(Color.Black), width + paddingX, paddingY, width + paddingX, height + paddingY);
            CreateGraphics().DrawLine(new Pen(Color.Black), paddingX, height + paddingY, width + paddingX, height + paddingY);

            for (int x = 0; x < divX - 1; x++)
            {
                CreateGraphics().DrawLine(new Pen(Color.Black), paddingX + ((width / divX) * (1 + x)), paddingY, paddingX + ((width / divX) * (1 + x)), height + paddingY);
            }

            for (int y = 0; y < divY - 1; y++)
            {
                CreateGraphics().DrawLine(new Pen(Color.Black), paddingX, paddingY + ((height / divY) * (1 + y)), width + paddingX, paddingY + ((height / divY) * (1 + y)));
            }
        }

        void DrawTileMap() {
            CreateGraphics().Clear(Color.White);
            GenerateGrid(gridWidth, gridHeight, divisionX, divisionY);

            for (int y = 0; y < tileMap.GetLength(1); y++) {
                for (int x = 0; x < tileMap.GetLength(0); x++) {
                    if (tileMap[x, y] == 1) GenerateTile(x * 10, y * 10, 10, 10, Color.Gray);
                }
            }
        }
    }
}
