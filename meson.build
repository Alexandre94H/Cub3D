project('cub3D', 'c', version : '1.0.0')

cc = meson.get_compiler('c')
cmake = import('cmake')

libm = cc.find_library('m')
libft = subproject('libft').get_variable('ft')
libgnl = subproject('get_next_line').get_variable('gnl')
libmlx = cmake.subproject('MLX42').dependency('mlx42')

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
