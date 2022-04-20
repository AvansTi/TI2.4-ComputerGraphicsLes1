#pragma warning disable CA1416 // Validate platform compatibility
using System.Diagnostics;
using System.Drawing;

var bitmap = new Bitmap(500, 500);

bitmap.SetPixel(100, 100, Color.Red);


bitmap.Save("out.png");
Process.Start("explorer", "out.png");