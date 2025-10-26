#include "../include/cub3d.h"

int	create_color(int red, int green, int blue) // renk değerlerini tek bir tamsayıya dönüştürür.
{
	return ((red << 16) | (green << 8) | blue); //red bileşeni 24 bitlik renk kodunun en başına (kırmızı kısmına) yerleştirilir. yeşil bileşen ortadaki 8 bite yerleşir. Üç renk bileşeni birleştirilir:
}
// İlk 8 bit: Kırmızı Sonraki 8 bit: Yeşil Son 8 bit: Mavi
int	parse_rgb_values(char *str, int *r, int *g, int *b) // bir renk satırını (örneğin "220,100,0") alır ve üç ayrı red, green, blue sayısına dönüştürür.
{
	char	**parts; // parts: ft_split ile virgüllere göre bölünmüş string dizisini tutacak.
	int		ret; // ret: fonksiyon sonunda başarılı mı (1) yoksa hata mı (0) döndürecek.

	if (!str)
		return (0);
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		free_split(parts);
		return (0);
	}
	*r = ft_atoi(parts[0]); // Her parçayı int’e çevirir:
	*g = ft_atoi(parts[1]);
	*b = ft_atoi(parts[2]);
	ret = 1; // Başlangıçta başarılı olduğunu varsayar.
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255) // Her rengin 0-255 aralığında olup olmadığını kontrol eder:
		ret = 0;
	free_split(parts);
	return (ret); // Sonuç olarak başarılı (1) veya hata (0) döner.
}

static int	get_color_values_from_line(char *line, t_color_parse_result *out) // renk satırını alır (örneğin "F 220,100,0" veya "C 225,30,0") ve içindeki RGB değerlerini ayrıştırır.
{
	char	*trimed; // trimed: satırın başındaki ve sonundaki boşluklar kaldırılmış hali.
	char	*values; // values: "F " veya "C " kısmından sonraki RGB değerlerini içeren string.

	trimed = ft_strtrim_whitespace(line); // Satırı boşluklardan temizler.
	if (!trimed)
		return (0);
	printf("treimmed: %s\n", trimed);
	printf("buradasfasdf\n");
	printf("line: %s\n", line);
	if (ft_strncmp(trimed, "F", 2) == 0) // Satırın "F " ile mi yoksa "C " ile mi başladığını kontrol eder.
		values = ft_strtrim_whitespace(trimed + 2); // "F " kısmından sonraki RGB değerlerini alır.
	else if (ft_strncmp(trimed, "C", 2) == 0) // "C " ile başlıyorsa
		values = ft_strtrim_whitespace(trimed + 2); // "C " kısmından sonraki RGB değerlerini alır.
	else
	{
		printf("buradasfasdf\n");
		free(trimed);
		return (0);
	}
	if (!values || !parse_rgb_values(values, &out->red,
			&out->green, &out->blue)) // RGB değerlerini ayrıştırır.
	{
		free(trimed);
		free(values);
		return (0);
	}
	out->trimed = trimed; // Sonuçları out yapısına atar.
	out->values = values; // values: RGB değerlerini içeren string.
	return (1);
}

int	parse_color_line(char *line, t_colors *colors) // renk satırını alır (örneğin "F 220,100,0" veya "C 225,30,0") ve t_colors yapısına ayrıştırılmış renk değerlerini atar.
{
	t_color_parse_result	res; // res: renk ayrıştırma sonucunu tutacak geçici yapı.

	if (!get_color_values_from_line(line, &res)) // Renk değerlerini satırdan alır.
		return (0);
	if (ft_strncmp(res.trimed, "F ", 2) == 0) // Satırın "F " ile mi başladığını kontrol eder.
	{
		colors->floor_red = res.red; // Renk bileşenlerini t_colors yapısına atar.
		colors->floor_green = res.green; // Renk bileşenlerini t_colors yapısına atar.
		colors->floor_blue = res.blue;
		colors->floor_color = create_color(res.red, res.green, res.blue); // Tek tamsayı renk değerini oluşturur.
		printf("Floor color: RGB(%d, %d, %d)\n", res.red, res.green, res.blue); // Konsola yazdırır.
	}
	else
	{
		colors->ceiling_red = res.red; // Renk bileşenlerini t_colors yapısına atar.
		colors->ceiling_green = res.green;
		colors->ceiling_blue = res.blue;
		colors->ceiling_color = create_color(res.red, res.green, res.blue); // Tek tamsayı renk değerini oluşturur.
		printf("Ceiling color: RGB(%d, %d, %d)\n", res.red, res.green, res.blue); // Konsola yazdırır.
	}
	printf("buradasfasdf\n");
	free(res.trimed);
	free(res.values);
	return (1);
}
