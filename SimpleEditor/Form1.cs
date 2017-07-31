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
                if (e.X < gridWidth + 10 && e.X > 10 && e.Y < gridHeight + 50 && e.Y > 50) {
                    if (tileMap[(e.X - 10) / (gridWidth / tileMap.GetLength(0)), (e.Y - 50) / (gridHeight / tileMap.GetLength(1))] == 0) {
                        GenerateTile(0, 0, 40, 40, Color.Gray);
                    }
                }
            }
        }

        int[,] tileMap;
        static int gridWidth = 800, gridHeight = 800, divisionX, divisionY;
        private void button1_Click(object sender, System.EventArgs e) {
            divisionX = (int)numericUpDown1.Value;
            divisionY = (int)numericUpDown2.Value;

            ResizeWindow();
            GenerateGrid(gridWidth, gridHeight, divisionX, divisionY);
            tileMap = new int[divisionX, divisionY];
        }

        void GenerateTile(int x, int y, int width, int height, Color color) {
            CreateGraphics().FillRectangle(new SolidBrush(color), x + 11, y + 51, width - 1, height - 1);
        }

        void GenerateGrid(int width, int height, int divX, int divY) {
            gridWidth = width;
            gridHeight = height;

            CreateGraphics().Clear(Color.White);
            CreateGraphics().DrawLine(new Pen(Color.Black), 10, 50, width + 10, 50);
            CreateGraphics().DrawLine(new Pen(Color.Black), 10, 50, 10, height + 50);
            CreateGraphics().DrawLine(new Pen(Color.Black), width + 10, 50, width + 10, height + 50);
            CreateGraphics().DrawLine(new Pen(Color.Black), 10, height + 50, width + 10, height + 50);

            for (int x = 0; x < divX - 1; x++)
            {
                CreateGraphics().DrawLine(new Pen(Color.Black), 10 + ((width / divX) * (1 + x)), 50, 10 + ((width / divX) * (1 + x)), height + 50);
            }

            for (int y = 0; y < divY - 1; y++)
            {
                CreateGraphics().DrawLine(new Pen(Color.Black), 10, 50 + ((height / divY) * (1 + y)), width + 10, 50 + ((height / divY) * (1 + y)));
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
