﻿using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace SimpleEditor {
    public partial class Form1 : Form {
        List<int[,]> structureList = new List<int[,]>();
        List<int[]> divisionList = new List<int[]>();
        int[,] tileMap;

        int previousSelectedIndex = -1;

        static int gridWidth = 800, gridHeight = 800, divisionX, divisionY;
        static int paddingX = 10, paddingY = 120;

        string savePath = "";

        enum Tile : int {
            NoTile = 0, //White
            RegularTile = 1 //Gray
        };

        public Form1() {
            InitializeComponent();

            checkBox1.CheckState = CheckState.Checked;

            Move += Form1_Move;
            Resize += Form1_Resize;

            MouseDown += Form1_MouseDown;
            MouseMove += Form1_MouseMove;
            MouseUp += Form1_MouseUp;
        }

        Color GetTileColor(int index) {
            if (index == 1) return Color.Gray;
            if (index == 2) return Color.Blue;
            return Color.White;
        }

        int mouseDrag = -1;
        private void Form1_MouseUp(object sender, MouseEventArgs e) { mouseDrag = -1; }

        private void Form1_MouseMove(object sender, MouseEventArgs e) {
            if (tileMap != null && mouseDrag != -1) {
                if (e.X < gridWidth + paddingX && e.X > paddingX && e.Y < gridHeight + paddingY && e.Y > paddingY) {
                    if (tileMap[(e.X - paddingX) / (gridWidth / tileMap.GetLength(0)), (e.Y - paddingY) / (gridHeight / tileMap.GetLength(1))] != mouseDrag) {
                        if (mouseDrag == 0) { GenerateTile((e.X - paddingX) / (gridWidth / divisionX) * (gridWidth / divisionX), (e.Y - paddingY) / (gridHeight / divisionY) * (gridHeight / divisionY), (gridWidth / divisionX), (gridHeight / divisionY), Color.White); }
                        else { GenerateTile((e.X - paddingX) / (gridWidth / divisionX) * (gridWidth / divisionX), (e.Y - paddingY) / (gridHeight / divisionY) * (gridHeight / divisionY), (gridWidth / divisionX), (gridHeight / divisionY), GetTileColor((int)numericUpDown3.Value)); }
                            tileMap[(e.X - paddingX) / (gridWidth / divisionX), (e.Y - paddingY) / (gridHeight / divisionY)] = mouseDrag;
                    }
                }
            }
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e) {
            if (tileMap != null) {
                if (e.X < gridWidth + paddingX && e.X > paddingX && e.Y < gridHeight + paddingY && e.Y > paddingY) {
                    if (tileMap[(e.X - paddingX) / (gridWidth / tileMap.GetLength(0)), (e.Y - paddingY) / (gridHeight / tileMap.GetLength(1))] != numericUpDown3.Value) {
                        GenerateTile((e.X - paddingX) / (gridWidth / divisionX) * (gridWidth / divisionX), (e.Y - paddingY) / (gridHeight / divisionY) * (gridHeight / divisionY), (gridWidth / divisionX), (gridHeight / divisionY), GetTileColor((int)numericUpDown3.Value));
                        tileMap[(e.X - paddingX) / (gridWidth / divisionX), (e.Y - paddingY) / (gridHeight / divisionY)] = (int)numericUpDown3.Value;
                        mouseDrag = (int)numericUpDown3.Value;
                    }
                    else {
                        GenerateTile((e.X - paddingX) / (gridWidth / divisionX) * (gridWidth / divisionX), (e.Y - paddingY) / (gridHeight / divisionY) * (gridHeight / divisionY), (gridWidth / divisionX), (gridHeight / divisionY), Color.White);
                        tileMap[(e.X - paddingX) / (gridWidth / divisionX), (e.Y - paddingY) / (gridHeight / divisionY)] = 0;
                        mouseDrag = 0;
                    }
                }
            }
        }

        void ResizeWindow() { Size = new Size(gridWidth + paddingX + 17, gridHeight + paddingY + 40); }

        private void Form1_Resize(object sender, System.EventArgs e) { ResizeWindow(); }
        private void Form1_Move(object sender, System.EventArgs e) {
            DrawTileMap();
        }

        private void checkBox1_CheckedChanged(object sender, System.EventArgs e) {
            DrawTileMap();
        }

        private void button2_Click(object sender, System.EventArgs e) {
            folderBrowserDialog1.ShowDialog();
            savePath = folderBrowserDialog1.SelectedPath;
            savePath += "\\" + "output" + ".txt";

            string output;
            int counter = 0;
            using (StreamWriter sw = File.CreateText(savePath)) {
                foreach (int[,] structure in structureList) {
                    output = listBox1.Items[counter].ToString();
                    output += "|";
                    output += divisionList[counter][0];
                    output += ",";
                    output += divisionList[counter][1];
                    output += "|";

                    for (int x = 0; x < structure.GetLength(1); x++) {
                        for (int y = 0; y < structure.GetLength(0); y++) {
                            if (structure[y, x] != 0) {
                                output += y + "," + x + "," + structure[y, x] + "|";
                            }
                        }
                    }

                    sw.WriteLine(output);
                    sw.WriteLine("");
                    counter += 1;
                }
            }
        }

        private void button3_Click(object sender, System.EventArgs e) {
            if (tileMap != null && listBox1.SelectedIndex != -1) {
                int[,] tempTileMap = structureList[listBox1.SelectedIndex].Clone() as int[,];
                divisionX = divisionList[listBox1.SelectedIndex][0];
                divisionY = divisionList[listBox1.SelectedIndex][1];
                tileMap = tempTileMap;
                DrawTileMap();
            }
        }

        private void button4_Click(object sender, System.EventArgs e) {
            if (tileMap != null) {
                if (listBox1.SelectedIndex != -1) {
                    int[,] tempTileMap = tileMap.Clone() as int[,];
                    structureList[listBox1.SelectedIndex] = tempTileMap;
                    divisionList.Add(new int[2] { divisionX, divisionY });
                }
                else {
                    int[,] tempTileMap = tileMap.Clone() as int[,];
                    structureList.Add(tempTileMap);
                    divisionList.Add(new int[2]{ divisionX, divisionY });
                    listBox1.Items.Add(textBox1.Text);
                }
            }
        }

        private void button5_Click(object sender, System.EventArgs e) {
            if (listBox1.SelectedIndex != -1) {
                structureList.RemoveAt(listBox1.SelectedIndex);
                divisionList.RemoveAt(listBox1.SelectedIndex);
                listBox1.Items.RemoveAt(listBox1.SelectedIndex);
            }
        }

        private void button6_Click(object sender, System.EventArgs e) {

        }

        private void listBox1_SelectedIndexChanged(object sender, System.EventArgs e) {
            if (previousSelectedIndex == listBox1.SelectedIndex && listBox1.SelectedIndex != -1) { listBox1.SelectedIndex = -1; }
            else { previousSelectedIndex = listBox1.SelectedIndex; }
        }

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
            if (tileMap != null) {
                CreateGraphics().Clear(Color.White);
                if (checkBox1.CheckState == CheckState.Checked)
                    GenerateGrid(gridWidth, gridHeight, divisionX, divisionY);

                for (int y = 0; y < tileMap.GetLength(1); y++) {
                    for (int x = 0; x < tileMap.GetLength(0); x++) {
                        if (tileMap[x, y] == 1) GenerateTile(x * (gridWidth / divisionX), y * (gridHeight / divisionY), (gridWidth / divisionX), (gridHeight / divisionY), Color.Gray);
                        if (tileMap[x, y] == 2) GenerateTile(x * (gridWidth / divisionX), y * (gridHeight / divisionY), (gridWidth / divisionX), (gridHeight / divisionY), Color.Blue);
                    }
                }
            }
        }
    }
}
