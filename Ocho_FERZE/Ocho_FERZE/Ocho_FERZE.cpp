#include <iostream>
#include <stdexcept>
#include "double_index.h"
#include "game.h"

int main()
{
    // Для текущего ферзя найти доступное поле
    // Если найти поле удалось:
    //   разместить на нем ферзя, посчитать все поля, которые он бьет и записать их в список битых полей.
    //   перейти к следующему ферзю. Или, если это восьмой ферзь - выйти со списком размещеных фигур.
    // Если найти поле не удалось:
    //   Если это первый ферзь - выйти с ошибкой о невозможности решить задачу
    //   Удалить текущего ферьзя из списков запр. полей
    //   Запомнить поле предыдущего ферзя в списке запрещенных полей для этого(предыдущего) ферьзя
    //   Удалить предыдущего ферзя, со всеми битыми им полями
    //   Сделать удаленного ферзя следующим
    //   перейти к следующему ферзю.

    // Доступное поле: список всех полей - список полей с размещенными ферзями - список битых полей - список запрещенных полей для этого ферьзя

    game game;

    int current_ferz = 0;

    try
    {
        while (true)
        {
            auto r = game.get_next_accepted_field(current_ferz);
            if (r.first)
            {
                game.place_frez(current_ferz, r.second);
                game.add_attaked_fields(current_ferz, game.calculate_atteked_fields(r.second));

                if (current_ferz == 7)
                    break;

                ++current_ferz;
            }
            else
            {
                if (current_ferz == 0)
                    throw std::logic_error("cant find solution");

                game.remove_from_forbidden_fields(current_ferz);

                --current_ferz;

                game.add_to_forbidden_fields(current_ferz, game.get_position(current_ferz));
                game.remove_from_attaked_fields(current_ferz);
                game.remove_ferz(current_ferz);
            }

        }
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 0;
    }

    for (int i = 0; i < 8; i++)
    {
        auto pos = game.get_position(i);
        std::pair<int, int> dp = double_index(pos);
        std::cout << "F: " << i << ", X: " << dp.first << ", Z: " << dp.second << std::endl;
    }

    return 0;
}
