project('Cub3D', 'c', version : '1.0.0')

cc = meson.get_compiler('c')

libm = cc.find_library('m')
libgnl = dependency('gnl')
libmlx = dependency('mlx')

src = files(
    'src/utils.c',
    'src/main.c',
    'src/parser/parser.c',
    'src/parser/header.c',
    'src/parser/map.c',
    'src/parser/populate.c',
    'src/hook/hook.c',
    'src/hook/movement.c',
    'src/hook/sort.c',
    'src/hook/rendering/floor.c',
    'src/hook/rendering/wall.c',
    'src/hook/rendering/sprite.c',
    'src/hook/rendering/draw.c',
)

inc = include_directories('include')

executable('cub3D', src,
           include_directories : inc,
           dependencies : [libm, libgnl, libmlx],
)
