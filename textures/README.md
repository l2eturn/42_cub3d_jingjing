# textures/

MLX42 โหลดได้เฉพาะ **PNG** (`mlx_load_png`).
ต้องมีไฟล์ 4 ทิศให้ตรงกับ path ใน `.cub`:

- `north.png`
- `south.png`
- `west.png`
- `east.png`

ขนาดแนะนำ power-of-two (เช่น 64x64) เพื่อให้ `& (tex_h - 1)` ใช้ได้ตอน map texel.
