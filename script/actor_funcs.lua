-- Funções da batalha, dos Actors, lembrando que todas 
-- elas recebem um Actor como primeiro parâmetro

function get_max_hp (act)
	return BASE_HP * (100 + 10 * act.vitality) / 100
end

function get_max_stamina (act)
	return BASE_STAMINA * (100 + act.vitality) / 100
end

function get_precision (act)
	return BASE_PRECISION + act.agility
end

function get_evasion (act)
	return act.agility
end

function get_stamina_recovery (act)
	--Uma porcentagem da estamina total, aumentada pela agilidade
	return BASE_STAMINA_REGEN * get_max_stamina (act) * (100 + act.agility) / 100
end

function get_phys_dmg_amplifier (act)
	return (100 + 2 * act.strength) / 100
end

function get_magic_dmg_amplifier (act)
	return (100 + 2 * act.inteligence) / 100
end

function get_phys_dmg_attenuation (act)
	return (100 + act.strength) / 100
end

function get_magic_dmg_attenuation (act)
	return (100 + act.inteligence) / 100
end
