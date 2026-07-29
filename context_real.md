# context_real.md — cub3D (project_real_42) Living Context

> ไฟล์นี้มีไว้ให้ **session ใหม่ catch-up ได้เร็ว** เวลา context เก่าเต็ม/หลุด
> อัพเดททุกครั้งที่จบ session หรือเปลี่ยน phase — ไม่ต้อง detail ยิบ ขอแค่พอให้กลับมาต่อได้ถูกจุด

---

## 1. ใครคุยด้วย / กติกา AI

- น้อง **"เตอร์"** — จุฬาฯ, เรียน 42Bangkok (target Level 9), พื้นฐาน C/Python/Bash/Docker/Linux
- ชอบ mentor แบบชี้จุดผิด + อธิบาย WHY มากกว่าเฉลยตรงๆ
- AI role: senior C/graphics engineer + 42 evaluator, พูดไทย, เรียกตัวเองว่า **"เฮีย"** เรียก user ว่า **"น้อง"**
- กติกาเต็ม: `../CLAUDE.md` (root) — override ทุกอย่าง ห้าม full solution ถ้าไม่ขอตรงๆ, ห้าม rewrite ทั้งก้อน, ห้าม comment อธิบาย WHAT

## 2. เอกสารอ้างอิงอื่นในโปรเจค (อย่า duplicate เนื้อหา ไปอ่านตรงนั้น)

| ไฟล์ | เนื้อหา |
|---|---|
| `../ter-setup/ter_background_profile.md` | โปรไฟล์/สไตล์การเรียนรู้ของน้อง |
| `../ter-setup/project_rules.md` | กติกา architecture + dev order (ต้นฉบับ) |
| `../ter-setup/shortnote.md` | สรุป spec สั้น (.cub format, controls, error rules) |
| `../ter-setup/4_Roadmap.md` | roadmap ละเอียดมาก 9 phase + traps แต่ละจุด |
| `../ter-setup/3_Struct_Design.md` | ที่มา/เหตุผลของทุก struct (t_game, t_mlx, t_map, t_player, t_texture, t_ray) + ownership tree |
| `../ter-setup/1_requirement_analysis.md`, `2_Architecture.md` | รายละเอียด spec/arch เพิ่มเติม (ยังไม่ได้อ่านรอบนี้) |
| `../md_files/walk_throught.md`, `compare.md` | เดิน walkthrough phase 6–21 (bonus ideas), เปรียบเทียบ ref implementations |
| `how_to.md` (ไฟล์นี้เดียวกัน folder) | **roadmap เวอร์ชันที่ผูกกับ scaffold จริงใน `project_real_42/` โดยตรง** — ใช้ไฟล์นี้เป็นหลักเวลาถามว่า "phase ไหนทำอะไร" |
| `../project_ref_mac/`, `../project_ref_linux/` | reference implementation เต็ม — เปิดดูได้เวลาติดจริง ห้ามลอกทั้งก้อน |

## 3. Scaffold คืออะไร

`project_real_42/` มี skeleton ครบแล้ว (Makefile build ผ่าน `-Werror`, ได้ binary จริง) แต่ **ทุก function body เป็น TODO/stub** — น้องต้องเติมทีละ phase ตาม `how_to.md`

โครง:
```
includes/cub3d.h   — struct + prototype ครบ (ตาม 3_Struct_Design.md)
maps/sample.cub     — map ทดสอบเล็ก
textures/           — รอใส่ PNG 4 ทิศ
src/{mlx,parsing,player,raycast,render,textures,events,cleanup,utils}/
```

Struct หลัก: `t_game` เป็นเจ้าของทุกอย่าง (mlx, map, player, tex[4], floor/ceil color) — ดู ownership tree เต็มใน `3_Struct_Design.md`

## 4. สถานะปัจจุบัน (อัพเดทล่าสุด: 2026-07-24)

### Build
- `make` ผ่าน ไม่มี warning/error — ยังไม่เคยรันแบบมีอะไรทำงานจริง (ทุก phase ยังเป็น stub)

### Phase progress (อิง `how_to.md`)

| Phase | เรื่อง | สถานะ |
|---|---|---|
| 1 | Window ขึ้นจอ (`mlx_init.c`, `main.c`) | ❌ ยังไม่เริ่ม — `init_mlx()` return 0 เฉยๆ, `main.c` ยัง comment `mlx_key_hook`/`loop_hook`/`mlx_loop` อยู่ |
| 2 | Parser (`parsing/*`, `utils/gnl.c`) | 🟡 เริ่มแตะแล้วแต่ค้าง — ดูหัวข้อ 5 |
| 3 | Validate map | ❌ ยังไม่เริ่ม (`validate_map.c` stub) |
| 4 | Player + raycast โครง | ❌ ยังไม่เริ่ม |
| 5 | Movement + rotation + collision | ❌ ยังไม่เริ่ม |
| 6 | Texture mapping | ❌ ยังไม่เริ่ม |
| 7 | Cleanup / error robustness | ❌ ยังไม่เริ่ม (มี prototype ใน `cleanup.c` เฉยๆ) |
| 8 | Bonus | ❌ ห้ามแตะจนกว่า mandatory จะนิ่ง |

> เฮียเคยแนะนำให้เริ่ม Phase 1 ก่อน (เห็นผลไว, debug ง่ายกว่า) แต่ของที่แตะจริงดันไปอยู่ Phase 2 — ยังไม่ตกลงกันว่าจะสางของค้างก่อนหรือย้อนกลับไป Phase 1

### 5. ของค้าง (uncommitted, ยังไม่ commit)

`src/parsing/parse_file.c:16` — เริ่มเขียนเช็ค `.cub` extension ใน `parse_cub()` แต่ทิ้งไว้กลางคัน:

```c
/* TODO: เช็คนามสกุล .cub ก่อนเปิด */
if ()                              // ← บรรทัด 16: syntax error ค้างอยู่ ไม่มีเงื่อนไขในวงเล็บ
fd = open(path, O_RDONLY);
```

**ผลกระทบ:** ตอนนี้ `make` จะ compile fail ทันทีถ้าลองรัน (ยังไม่ได้ลองจริงในรอบนี้ — ควรเช็คซ้ำตอนกลับมาทำต่อ)
**สิ่งที่ต้องทำต่อ:** เติมเงื่อนไขเช็คนามสกุล (เช่นเทียบ suffix `.cub` ของ `path` ด้วย `ft_strlen`/`ft_strncmp` เอง — ไม่ใช้ libc string search แบบสำเร็จรูปถ้า norm ห้าม) แล้วค่อย `open()` ต่อ

### 6. Decision log

- 2026-07-24: เตอร์ประกาศจะเริ่มเขียนเองใหม่จาก `project_real_42` — เฮียสำรวจสถานะ ยังไม่ได้ตัดสินใจว่าจะเริ่มจาก Phase 1 หรือสางของค้างใน parse_file.c ก่อน (รอน้องตอบรอบหน้า)

---

## วิธี update ไฟล์นี้ (ทำทุกจบ session)

1. อัพเดทตาราง Phase progress ถ้ามี phase ไหนเสร็จ/เริ่มใหม่
2. ย้าย "ของค้าง" ที่แก้แล้วออก เพิ่มของค้างใหม่ (ถ้ามี)
3. เพิ่มบรรทัดใหม่ใน Decision log (วันที่ + สรุปสั้นๆ ว่าตัดสินใจ/เปลี่ยนแนวทางอะไร) — ไม่ต้อง log ทุกการกระทำ เอาแค่จุดที่กระทบทิศทางงาน
