project('Cub3D', 'c', version : '1.0.0')

cc = meson.get_compiler('c')

libm = cc.find_library('m')
libgnl = dependency('gnl')
libmlx = dependency('mlx')

src = files(
    'src/utils.c',
    'src/main.c',
    'src/parser.c',
    'src/loop.c',
    'src/hook.c',
)

inc = include_directories('include')

executable('cub3D', src,
           include_directories : inc,
           dependencies : [libm, libgnl, libmlx],
)
