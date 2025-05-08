#include "minishell.h"
// Built-in komutların yönetimi
//- cd: Dizin değiştirme
//- echo: Ekrana yazdırma
//- pwd: Mevcut dizini gösterme
//- export: Çevre değişkeni ekleme/değiştirme
//- unset: Çevre değişkeni silme
//- env: Çevre değişkenlerini listeleme
//- exit: Shell'den çıkış


//int	ft_cd(t_minishell *minishell)
//{
//	int		chdir_tmp;
//	char	*cwd;
//
//	cwd = getcwd(NULL, 0);		//0 gerekli boyutu otomatik hesaplar.NULL otomatik bellek ayırır
//
//	if ()
//	chdir_tmp = chdir(cwd);
//	if (chdir_tmp == -1)
//	{
//		perror("cd");
//		return (1);
//	}
//	free(cwd);
//	return (0);
//}
//
//int	ft_echo()
//{
//
//}
//
//int	ft_pwd()
//{
//
//}
//
//int	ft_export()
//{
//
//}


// Hayır, tüm built-in komutların parent process'te çalışması zorunlu değil. Komutları analiz edelim:
// 
// 1. Kesinlikle Parent Process'te Çalışması Gerekenler:
//    - cd: Working directory değişikliği shell'i etkilemeli
//    - export: Environment değişkenleri shell'de kalıcı olmalı
//    - unset: Environment değişkenleri shell'de kalıcı olmalı
//    - exit: Shell'i sonlandırmalı
// 
// 2. Child Process'te de Çalışabilecekler:
//    - echo: Sadece output üretir
//    - pwd: Sadece mevcut dizini gösterir
//    - env: Sadece environment değişkenlerini listeler
// 
// Ancak performans ve tutarlılık açısından:
// - Tüm built-in'leri aynı şekilde (parent'ta) yönetmek daha mantıklı
// - Fork maliyetinden kaçınmış oluruz
// - Kod karmaşıklığını azaltırız