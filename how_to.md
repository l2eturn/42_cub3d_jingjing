# cub3D — How To (build ตั้งแต่ศูนย์)

คู่มือนี้พาน้อง build cub3D เองทีละ phase บน scaffold ที่วางไว้แล้ว
เป้าหมาย: **เข้าใจ WHY ทุกก้าว ไม่ใช่ลอก**. ทุกไฟล์ใน `src/` มี `TODO` + comment WHY อยู่แล้ว
งานของน้องคือเติมเนื้อในตามลำดับข้างล่าง แล้ว build บ่อยๆ

> ref เต็ม: `../project_ref_mac/` — เปิดดูได้เวลาติดจริง แต่ **อย่าลอกทั้งก้อน**
> spec ละเอียด: `../md_files/walk_throught.md`, `../cub3d_en.subject.pdf`

---

## 0. สิ่งที่มีให้แล้ว (base)

```
project_real_42/
├── Makefile              ← พร้อมใช้ (build MLX42 ให้อัตโนมัติ)
├── includes/cub3d.h      ← struct + prototype ครบ (mandatory)
├── maps/sample.cub       ← map ทดสอบเล็กๆ
├── textures/             ← เอา PNG 4 ทิศมาใส่เอง
└── src/                  ← โครงครบ ทุกไฟล์เป็น stub รอเติม
```

**สถานะตอนนี้:** `make` ผ่าน `-Werror` และได้ binary จริง แต่ยังไม่ทำอะไร (ทุก body เป็น TODO)
→ น้องเติมทีละ phase แล้ว binary จะค่อยๆ มีชีวิต

### Build / Run

```bash
make            # build (ครั้งแรกจะ compile MLX42 ด้วย ~1-2 นาที)
./cub3D maps/sample.cub
make re         # rebuild หมด
make fclean     # ลบ .o + binary
```

---

## หลักคิดกลาง (อย่าลืม)

1. **Parse → Validate → Render** — ห้าม render ตอน map ยังไม่ valid
2. **ownership ชัด** — `t_game` เป็นเจ้าของทุก alloc, free ที่ `cleanup.c` ที่เดียว
3. **error ออกทาง stderr** เป็น `"Error\n"` + ข้อความ แล้ว exit สะอาด (valgrind ต้องนิ่ง)
4. **build บ่อย** — เขียนทีละ 1 function แล้ว `make` อย่าเขียนยาวแล้วค่อย compile

---

## Phase 1 — Window ขึ้นจอ (ไฟล์: `mlx/mlx_init.c`, `main.c`)

**เป้า:** เปิดหน้าต่างดำๆ ปิดด้วย ESC ได้ = MLX ใช้งานได้

1. เติม `init_mlx()`:
   - `game->mlx.mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);` (NULL → error)
   - สร้าง screen image + `mlx_image_to_window`
2. ใน `main.c` ปลด comment 3 บรรทัดท้าย: `mlx_key_hook`, `mlx_loop_hook`, `mlx_loop`
3. เติม `close_hook` + ESC ใน `key_hook` ให้ปิดได้

**เช็ค:** `./cub3D maps/sample.cub` → หน้าต่างเปิด, ESC ปิด, ไม่ leak

> WHY วาดลง image เดียว: เร็วกว่า put ตรง window และ MLX คุม buffer ให้

---

## Phase 2 — Parser (.cub) (ไฟล์: `parsing/*`, `utils/gnl.c`)

**เป้า:** อ่านไฟล์ → ได้ element (path/สี) + grid ในหน่วยความจำ

ก่อนเริ่ม: วาง **get_next_line + ft_split ของน้องเอง** ลงใน `utils/gnl.c` (ตอนนี้เป็น stub คืน NULL)

ลำดับเติม:
1. `parse_cub` — เช็คนามสกุล `.cub`, เปิดไฟล์ (มีโครงให้แล้ว)
2. `parse_elements` — วน gnl, บรรทัดไหนเป็น NO/SO/WE/EA/F/C → `parse_element_line`;
   เจอบรรทัด map (ขึ้นต้น `0`/`1`/space) → เก็บใส่ `*first_map_line` แล้ว break
3. `parse_element_line` — split → เก็บ path (`ft_strdup`) / แปลงสี `R,G,B` → int
4. `parse_map` — เอา `first_line` + gnl ที่เหลือมาต่อเป็น `grid`

**Edge cases ที่ evaluator ชอบลอง:**
- element ซ้ำ / ขาด / สีเกิน 255 / มีอย่างอื่นหลัง map
- ไฟล์ว่าง / เปิดไม่ได้ / path texture ผิด

> WHY เก็บ path เป็น string ก่อน แล้วค่อย load PNG ทีหลัง: แยก parse (ตรวจ) ออกจาก MLX (side-effect) — validate พังก็ไม่เสียเวลา decode

---

## Phase 3 — Validate map (ไฟล์: `parsing/validate_map.c`)

**เป้า:** ปฏิเสธ map ที่เล่นไม่ได้ ก่อนถึง render

1. หา player char (`N/S/E/W`) — ต้องเจอ **พอดี 1 ตัว** → `init_player()` แล้วแทนด้วย `'0'`
2. เช็ค charset: อนุญาตแค่ `0 1 space` (+ player char ก่อนถูกแทน)
3. **flood fill** จากตำแหน่ง player บน **copy ของ grid**:
   - เดินไป 4 ทิศ ผ่านเฉพาะ `'0'`
   - ถ้าเดินไปแตะ **ขอบ map หรือ space** → map รั่ว → error

> WHY flood fill ไม่ใช่แค่เช็คขอบ: จับรูรั่วที่อยู่กลาง map (ช่อง `0` ติด space) ได้ครบทุกกรณี
> WHY ทำบน copy: flood fill ต้อง mark ช่องที่เดินแล้ว ห้ามทำลาย grid จริงที่ต้องใช้ render

---

## Phase 4 — Player + raycast โครง (ไฟล์: `player/player.c`, `raycast/raycast.c`, `render/*`)

**เป้า:** เห็นกำแพงเป็นแท่งสีตัน (ยังไม่ต้อง texture) = 3D ใช้ได้

1. `init_player` — ตั้ง pos กลาง cell, dir/plane ตามทิศ spawn
2. `raycast.c` ทั้ง 4 ฟังก์ชัน (init_ray → init_step → perform_dda → calc_wall_data) — ทำตาม TODO
3. `render_flat.c` — เติมพื้น/เพดานด้วย `floor_color`/`ceil_color`
4. `render_wall.c` — ชั่วคราววาดแท่งสีตัน (เช่น side==1 สีเข้มกว่า) ตาม `draw_start..draw_end`
5. `render_frame.c` — ปลด TODO วน raycast ทุกคอลัมน์
6. `events.c` `loop_hook` — เรียก `render_frame` ทุกเฟรม

**เช็ค:** เปิดมาเห็นกำแพงเป็นแท่ง มี perspective (ไกล = เตี้ย)

> WHY `perp_wall_dist` ไม่ใช่ระยะตรง: กัน fisheye (ขอบจอโค้ง)
> WHY camera plane: `|plane|/|dir| = tan(FOV/2)` → คุมมุมมอง

---

## Phase 5 — Movement + rotation + collision (ไฟล์: `player/player.c`, `events/events.c`)

**เป้า:** WASD เดิน, ←/→ หมุน, ชนกำแพงไม่ทะลุ

1. `key_hook` — press/release → set/clear `move_fb`, `move_lr`, `rotate`
2. `update_player`:
   - หมุน: คูณ dir & plane ด้วย rotation matrix (มุม = `rotate * ROT_SPEED`)
   - เดิน: บวก dir/plane × `MOVE_SPEED`
   - **collision แยกแกน**: เช็ค x กับ y แยกกัน → ไถลตามกำแพงได้ (`is_blocked`)

> WHY แยก flag ออกจาก key event: กดค้าง = เดินต่อเนื่องลื่น ไม่ผูก key-repeat ของ OS
> WHY collision แยกแกน: ชนกำแพงแล้วยังเลื่อนอีกแกนได้ ไม่หนืดติดมุม

---

## Phase 6 — Texture mapping (ไฟล์: `textures/texture_load.c`, `render/render_wall.c`)

**เป้า:** กำแพงมี texture จริงตาม 4 ทิศ

1. เอา PNG 4 ไฟล์ใส่ `textures/` (ดู `textures/README.md`)
2. `load_textures` — `mlx_load_png` ทั้ง 4, เก็บ width/height
3. `draw_column`:
   - เลือก texture จาก `side` + ทิศ ray (NO/SO/WE/EA)
   - `wall_x` → `tex_x`
   - map แต่ละ pixel → `tex_y` ตามสัดส่วนความสูง, อ่าน texel, `put_pixel`

> WHY แนะนำ texture power-of-two: ใช้ `& (tex_h-1)` แทน `%` ได้ เร็วและกัน index หลุด

---

## Phase 7 — Cleanup + error robustness (ไฟล์: `cleanup/cleanup.c`)

**เป้า:** valgrind สะอาด, ไม่ leak/double-free ทุกทางออก

- `cleanup_exit` — free ทุก alloc (grid, tex_path, image, mlx) แบบทน NULL
- ทุก error path ใน main ผ่าน `cleanup_exit` ที่เดียว
- ทดสอบ: map พัง, ไฟล์ไม่มี, texture ผิด, ESC ระหว่างเล่น → ต้อง exit สะอาดหมด

```bash
# Linux: valgrind --leak-check=full ./cub3D maps/sample.cub
# macOS: leaks --atExit -- ./cub3D maps/sample.cub
```

> หมายเหตุ: MLX42/glfw อาจมี "still reachable" ของมันเอง — โฟกัส leak ที่ **โค้ดเราalloc** เอง

---

## Phase 8 — Bonus (ทำหลัง mandatory ผ่าน eval)

ดู `../project_ref_mac/src/bonus/` + walkthrough Phase 6–21 เป็นไอเดีย:
minimap, doors, sprites (Z-buffer), mouse look, HUD, ...
**อย่าเพิ่งแตะจนกว่า mandatory จะนิ่ง 100%** — bonus นับ 0 ทันทีถ้า mandatory ไม่ครบ

---

## ลำดับแนะนำสั้นๆ

```
1 window → 2 parse → 3 validate → 4 ray(แท่งสี) → 5 move → 6 texture → 7 cleanup → 8 bonus
```

ทุก phase: เขียน → `make` → รัน → เช็ค แล้วค่อยไปต่อ. ติดตรงไหนถามเฮียได้เลย 🔧
