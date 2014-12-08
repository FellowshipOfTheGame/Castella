-- Funções da batalha, dos Actors, lembrando que todas 
-- elas recebem um Actor como primeiro parâmetro

function max_hp (act)
	return Actor.BASE_HP * (100 + 10 * act.vitality) / 100
end

function max_stamina (act)
    return Actor.BASE_STAMINA * (100 + act.vitality) / 100
end

function precision (act)
    return Actor.BASE_PRECISION + act.agility
end

function evasion (act)
    return act.agility
end

function stamina_recovery (act)
    --Uma porcentagem da estamina total, aumentada pela agilidade
    return Actor.BASE_STAMINA_REGEN * max_stamina (act) * (100 + act.agility) / 100
end

function phys_dmg_amplifier (act)
    return (100 + 2 * act.strength) / 100
end

function magic_dmg_amplifier (act)
    return (100 + 2 * act.inteligence) / 100
end

function phys_dmg_attenuation (act)
    return (100 + act.strength) / 100
end

function magic_dmg_attenuation (act)
    return (100 + act.inteligence) / 100
end
