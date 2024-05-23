project('Cub3D', 'c', version : '1.0.0')

cc = meson.get_compiler('c')

libm = cc.find_library('m')
libft = dependency('ft')
libgnl = dependency('gnl')
libmlx = dependency('mlx')

src = files(
    'src/main.c',
    'src/file.c',
    'src/loop.c',
    'src/hook.c'
)

inc = include_directories('include')

executable('cub3D', src,
    include_directories : inc,
    dependencies : [libm, libft, libgnl, libmlx],
)
